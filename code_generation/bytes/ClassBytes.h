//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_CLASSBYTES_H
#define PHP_COMPILER_CLASSBYTES_H


#include <utility>

#include "ValueAndBytes.h"
#include "code_generation/ConstantValue.h"
#include "FieldBytes.h"
#include "MethodBytes.h"
#include "code_generation/attributes/SourceFileAttribute.h"

class ClassBytes {
private:
    static ValueAndBytes magicConst;
    static ValueAndBytes versionClassFile;

    ConstantValue name;
    ConstantValue superClass;
    Flags flags;
    vector<FieldBytes> fields;
    vector<MethodBytes> methods;
    SourceFileAttribute *sourceFile;

    vector<ConstantValue> *consts;

    bool isCreatedClassConst = false;
    bool isCreatedSuperClassConst = false;

public:
    ClassBytes(Flags flags, const ConstantValue& name, const ConstantValue& superClass, SourceFileAttribute *file,
               vector<ConstantValue> *consts)
            : flags(flags), name(name), superClass(superClass), sourceFile(file), consts(consts) {
        if (name.getTypeConst() != C_Utf8) throw runtime_error("Name is not Utf-8");
        if (superClass.getTypeConst() != C_Utf8) throw runtime_error("Super class is not Utf-8");
    }

    void addField(const FieldBytes& field) {
        fields.push_back(field);
    }

    void addMethod(const MethodBytes& method) {
        methods.push_back(method);
    }

    vector<ConstantValue> *getConsts() {
        return consts;
    }

    ConstantValue createClassConst() {
        isCreatedClassConst = true;
        return ConstantValue::CreateClass(name, consts);
    }

    ConstantValue createSuperClassConst() {
        isCreatedSuperClassConst = true;
        return ConstantValue::CreateClass(superClass, consts);
    }

    vector<ValueAndBytes> classToBytes() {
        if (!isCreatedClassConst) createClassConst();
        if (!isCreatedSuperClassConst) createSuperClassConst();

        auto res = vector<ValueAndBytes>();
        res.emplace_back((int) 0xCAFEBABE, 4);
        auto version = ValueAndBytes(65, 4);
        res.push_back(version);
        //consts
        auto countConsts = ValueAndBytes((int) consts->size() + 1, 2);
        res.push_back(countConsts);
        for (const auto &constValue: *consts) {
            auto tagConst = constValue.getTypeConst();
            auto bytesConst = ValueAndBytes(tagConst, 1);
            res.push_back(bytesConst); //tag const
            if (tagConst == C_Utf8) res.emplace_back(constValue.getValue().getBytes(), 2);
            res.push_back(constValue.getValue()); //value const
        }
        //flags
        res.push_back(*flags.flagToBytes());
        //this class
        res.emplace_back(
                ConstantValue::getIdConstByString(consts, name.getIdString(), C_Class), 2);
        //super class
        res.emplace_back(
                ConstantValue::getIdConstByString(consts, superClass.getIdString(), C_Class), 2);
        //interfaces
        res.emplace_back((int) 0, 2);
        //fields
        res.emplace_back((int) fields.size(), 2);
        for (auto field: fields) {
            auto fieldBytes = field.fieldToBytes();
            res.insert(res.end(), fieldBytes.begin(), fieldBytes.end());
        }
        //methods
        res.emplace_back((int) methods.size(), 2);
        for (const auto& method: methods) {
            auto methodBytes = method.methodToBytes(*consts);
            res.insert(res.end(), methodBytes.begin(), methodBytes.end());
        }
        //source file attribute
        res.emplace_back(1, 2);
        auto sourceBytes = sourceFile->attributeToBytes();
        res.insert(res.end(), sourceBytes.begin(), sourceBytes.end());

        return res;
    }

    static ClassBytes *
    fromClassStmtDeclNode(ClassStmtDeclNode *node, Flags &flags, const string& superClass, SourceFileAttribute *sourceFile,
                          vector<ConstantValue> *consts) {

        if (node == nullptr) return nullptr;

        auto tmp_name = ConstantValue::CreateUtf8(*node->class_def->class_id, consts);
        auto tmp_super = ConstantValue::getConstantByString(consts, superClass);

        auto tmp_class = new ClassBytes(
                flags,
                tmp_name,
                tmp_super,
                sourceFile,
                consts
        );

        for (auto i: node->class_stmt_list->vector) {
            switch (i->type) {
                case function_def:
                    tmp_class->addMethod(
                            MethodBytes::fromFunctionStmtDecl(i->function_stmt_decl,
                                                              i->access_mod,
                                                              consts));
                    break;
                case function_decl_type:
                    tmp_class->addMethod(
                            MethodBytes::fromFunctionDefStmtDecl(i->function_def, *Flags::convertToFlags(i->access_mod),
                                                                 consts));
                    break;
                case class_expr_stmt_type:
                    tmp_class->addField(FieldBytes::fromStmtExpr(i->class_expr, consts));
                    break;
                default:
                    break;
            }
        }

        return tmp_class;
    }

    // От старта
    static ClassBytes *fromStartStmt(StartNode *node, SourceFileAttribute *sourceFile,
                                     vector<ConstantValue> *consts) {
        if (node == nullptr) return nullptr;

        auto tmp_name = ConstantValue::CreateUtf8(string("_main"), consts);

        if (ConstantValue::getIdConstByString(consts, string("java/lang/Object")) == -1)
            ConstantValue::CreateUtf8(string("java/lang/Object"), consts);
        auto tmp_super = ConstantValue::getConstantByString(consts, string("java/lang/Object"));

        auto tmp_class = new ClassBytes(
                Flags(ACC_PUBLIC + ACC_SUPER),
                tmp_name,
                tmp_super,
                sourceFile,
                consts
        );
        auto stmtList = vector<StmtNode *>();

        tmp_class->addMethod(MethodBytes::generateInitMethod(consts));

        for (auto i: node->top_stmt_list->vector) {
            switch (i->type) {
                case function_top_type:
                    tmp_class->addMethod(
                            MethodBytes::fromFunctionStmtDecl(i->func_stmt_decl,
                                                              ClassAccessModList::CreateNode(
                                                                      ClassAccessModNode::CreateNode(
                                                                              ClassAccessMod::static_node)),
                                                              consts));
                    break;
                case stmt_top_type:
                    stmtList.push_back(i->stmt);
                    break;
                default:
                    break;
            }
        }

        auto mainFunctionName = ConstantValue::CreateUtf8(string("main"), consts);

        auto mainFunctionDesc = ConstantValue::CreateUtf8(string("([Ljava/lang/String;)V"), consts);

        auto mainParams = new vector<string>();
        mainParams->push_back(string("args"));

        auto codeList = new StmtList();

        codeList->vector = stmtList;

        for (auto stmtNode: codeList->vector) {
            MethodBytes::findAllConstInStmtNode(stmtNode, consts);
        }

        const CodeAttribute *tmpCode = CodeAttribute::fromStmtList(codeList, 1000, mainParams, consts);

        auto mainFunction = MethodBytes(Flags(ACC_STATIC + ACC_PUBLIC), mainFunctionName, mainFunctionDesc,
                                        tmpCode, consts);

        tmp_class->addMethod(mainFunction);

        return tmp_class;
    }


    // На будущее
    static ClassBytes *fromInterfaceStmtDecl(InterfaceStmtDeclNode *node, Flags &flags, const string& superClass,
                                             SourceFileAttribute *sourceFile,
                                             vector<ConstantValue> *consts) {
        if (node == nullptr) return nullptr;

        auto tmp_name = ConstantValue::CreateUtf8(*node->expr_definition->id, consts);
        auto tmp_super = ConstantValue::getConstantByString(consts, superClass);

        auto tmp_class = new ClassBytes(
                flags,
                tmp_name,
                tmp_super,
                sourceFile,
                consts
        );

        for (auto i: node->stmt_list->vector) {

            tmp_class->addMethod(
                    MethodBytes::fromFunctionDefStmtDecl(i->function_def, *Flags::convertToFlags(i->access_mod),
                                                         consts));
        }

        return tmp_class;
    }
};

#endif //PHP_COMPILER_CLASSBYTES_H
