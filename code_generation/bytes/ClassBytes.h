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

    vector<const ValueAndBytes *> classToBytes() {
        auto res = vector<const ValueAndBytes *>();
        res.push_back(new ValueAndBytes((int) 0xCAFEBABE, 4));
        res.push_back(new ValueAndBytes(65, 4));
        //consts
        res.push_back(new ValueAndBytes((int) consts->size(), 2));
        for (auto constValue: *consts) {
            res.push_back(new ValueAndBytes(constValue->getTypeConst(), 1)); //tag const
            res.push_back(constValue->getValue()); //value const
        }
        //flags
        res.push_back(flags.flagToBytes());
        //name
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *name), 2)); //TODO возвращает хрень
        //super class
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *superClass), 2));
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
            auto methodBytes = method->methodToBytes();
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
                                                              *Flags::convertToFlags(i->access_mod),
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
            }
        }

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
