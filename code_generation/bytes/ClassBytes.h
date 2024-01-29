//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_CLASSBYTES_H
#define PHP_COMPILER_CLASSBYTES_H


#include "ValueAndBytes.h"
#include "code_generation/ConstantValue.h"
#include "FieldBytes.h"
#include "MethodBytes.h"
#include "code_generation/attributes/SourceFileAttribute.h"

class ClassBytes {
private:
    static ValueAndBytes magicConst;
    static ValueAndBytes versionClassFile;

    ConstantValue *name;
    ConstantValue *superClass;
    Flags flags;
    vector<FieldBytes *> fields;
    vector<MethodBytes *> methods;
    SourceFileAttribute *sourceFile;

    vector<ConstantValue *> *consts;

    bool isCreatedClassConst = false;
    bool isCreatedSuperClassConst = false;

public:
    ClassBytes(Flags flags, ConstantValue *name, ConstantValue *superClass, SourceFileAttribute *file,
               vector<ConstantValue *> *consts)
            : flags(flags), name(name), superClass(superClass), sourceFile(file), consts(consts) {
        if (name->getTypeConst() != C_Utf8) throw runtime_error("Name is not Utf-8");
        if (superClass->getTypeConst() != C_Utf8) throw runtime_error("Super class is not Utf-8");
    }

    void addField(FieldBytes *field) {
        fields.push_back(field);
    }

    void addMethod(MethodBytes *method) {
        methods.push_back(method);
    }

    vector<ConstantValue *> *getConsts() {
        return consts;
    }

    ConstantValue *createClassConst() {
        isCreatedClassConst = true;
        return ConstantValue::CreateClass(name, consts);
    }

    ConstantValue *createSuperClassConst() {
        isCreatedSuperClassConst = true;
        return ConstantValue::CreateClass(superClass, consts);
    }

    vector<const ValueAndBytes *> classToBytes() {
        if (!isCreatedClassConst) createClassConst();
        if (!isCreatedSuperClassConst) createSuperClassConst();

        auto res = vector<const ValueAndBytes *>();
        res.push_back(new ValueAndBytes((int) 0xCAFEBABE, 4));
        res.push_back(new ValueAndBytes(65, 4));
        //consts
        res.push_back(new ValueAndBytes((int) consts->size(), 2));
        for (auto constValue: *consts) {
            auto tagConst = constValue->getTypeConst();
            res.push_back(new ValueAndBytes(tagConst, 1)); //tag const
            if (tagConst == C_Utf8) res.push_back(new ValueAndBytes(constValue->getValue()->getBytes(), 2));
            res.push_back(constValue->getValue()); //value const
        }
        //flags
        res.push_back(flags.flagToBytes());
        //this class
        res.push_back(new ValueAndBytes(
                ConstantValue::getIdConstByString(consts, name->getIdString(), C_Class), 2));
        //super class
        res.push_back(new ValueAndBytes(
                ConstantValue::getIdConstByString(consts, superClass->getIdString(), C_Class), 2));
        //interfaces
        res.push_back(new ValueAndBytes((int) 0, 2));
        //fields
        res.push_back(new ValueAndBytes((int) fields.size(), 2));
        for (auto field: fields) {
            auto fieldBytes = field->fieldToBytes();
            res.insert(res.end(), fieldBytes.begin(), fieldBytes.end());
        }
        //methods
        res.push_back(new ValueAndBytes((int) methods.size(), 2));
        for (auto method: methods) {
            auto methodBytes = method->methodToBytes(consts);
            res.insert(res.end(), methodBytes.begin(), methodBytes.end());
        }
        //source file attribute
        res.push_back(new ValueAndBytes(1, 2));
        auto sourceBytes = sourceFile->attributeToBytes();
        res.insert(res.end(), sourceBytes.begin(), sourceBytes.end());

        return res;
    }

    static ClassBytes *
    fromClassStmtDeclNode(ClassStmtDeclNode *node, Flags &flags, string *superClass, SourceFileAttribute *sourceFile,
                          vector<ConstantValue *> *consts) {

        if (node == nullptr) return nullptr;

        auto tmp_name = ConstantValue::CreateUtf8(node->class_def->class_id, consts);
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
                                     vector<ConstantValue *> *consts) {
        if (node == nullptr) return nullptr;

        auto tmp_name = ConstantValue::CreateUtf8(new string("<main>"), consts);

        if (ConstantValue::getIdConstByString(consts, new string("java/lang/Object")) == -1)
            ConstantValue::CreateUtf8(new string("java/lang/Object"), consts);
        auto tmp_super = ConstantValue::getConstantByString(consts, new string("java/lang/Object"));

        auto tmp_class = new ClassBytes(
                Flags(ACC_PUBLIC + ACC_SUPER),
                tmp_name,
                tmp_super,
                sourceFile,
                consts
        );
        auto stmtList = vector<StmtNode *>();

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

        auto mainFunctionName = ConstantValue::CreateUtf8(new string("main"), consts);

        auto mainFunctionDesc = ConstantValue::CreateUtf8(new string("([LJava/lang/String;)V"), consts);

        auto mainParams = vector<string *>();
        mainParams.push_back(new string("args"));

        auto codeList = new StmtList();

        codeList->vector = stmtList;

        auto mainFunction = MethodBytes(Flags(ACC_STATIC + ACC_PUBLIC), mainFunctionName, mainFunctionDesc,
                                        CodeAttribute::fromStmtList(codeList, 1000, mainParams, consts), consts);

        tmp_class->addMethod(&mainFunction);

        return tmp_class;
    }


    // На будущее
    static ClassBytes *fromInterfaceStmtDecl(InterfaceStmtDeclNode *node, Flags &flags, string *superClass,
                                             SourceFileAttribute *sourceFile,
                                             vector<ConstantValue *> *consts) {
        if (node == nullptr) return nullptr;

        auto tmp_name = ConstantValue::CreateUtf8(node->expr_definition->id, consts);
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
