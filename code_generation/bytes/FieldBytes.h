//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_FIELDBYTES_H
#define PHP_COMPILER_FIELDBYTES_H


#include "code_generation/ConstantValue.h"
#include "WriteBytesToFile.h"
#include "Flags.h"
#include "code_generation/attributes/ConstantValueAttribute.h"
#include "parser_classes/ConstDecl/ConstDeclNode.hpp"
#include "parser_classes/Vector_classes/ConstDeclList/ConstDeclList.hpp"
#include "parser_classes/ClassStmt/ClassExprNode.hpp"

class FieldBytes {
private:
    vector<ConstantValue *> *consts;
    Flags flags;
    ConstantValue fieldName;
    ConstantValue descriptor;
    vector<ConstantValueAttribute *> attributes;
public:
    FieldBytes(ConstantValue &fieldName, ConstantValue &descriptor, Flags &flags, vector<ConstantValue *> *consts) :
            descriptor(descriptor), fieldName(fieldName), flags(flags), consts(consts) {
        if (fieldName.getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Field name is not utf-8 type");
        if (descriptor.getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Descriptor is not utf-8 type");
    }

    FieldBytes(ConstantValue &fieldName, ConstantValue &descriptor, Flags &flags,
               vector<ConstantValueAttribute *> &attributes, vector<ConstantValue *> *consts) :
            descriptor(descriptor), fieldName(fieldName), flags(flags), consts(consts), attributes(attributes) {
        if (fieldName.getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Field name is not utf-8 type");
        if (descriptor.getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Descriptor is not utf-8 type");
    }

    void setAttributes(vector<ConstantValueAttribute *> &attr) {
        attributes = attr;
    }

    void addAttribute(ConstantValueAttribute *attr) {
        attributes.push_back(attr);
    }

    vector<const ValueAndBytes *> fieldToBytes() {
        vector<const ValueAndBytes *> res;
        //flags
        res.push_back(flags.flagToBytes());
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, fieldName), 2));
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, descriptor), 2));

        res.push_back(new ValueAndBytes((int) attributes.size(), 2));

        for (auto *attr: attributes) {
            auto attrBytes = attr->attributeToBytes();
            res.insert(res.end(), attrBytes.begin(), attrBytes.end());
        }

        return res;
    }

    static FieldBytes *fromConstDeclNode(ConstDeclNode *node, Flags flag, vector<ConstantValue *> *consts) {
        if (node == nullptr) return nullptr;


        auto tmp_name = ConstantValue::CreateUtf8(node->id, consts);

        auto tmp_type = ConstantValue::getConstantByString(consts, new string("RTL/Value;"))
                        ?: ConstantValue::CreateUtf8(new string("RTL/Value;"), consts);

        auto tmp = new FieldBytes(
                *tmp_name,
                *tmp_type,
                flag,
                consts
        );

        return tmp;
    }

    static FieldBytes *fromStmtExpr(ClassExprNode *node, vector<ConstantValue *> *consts) {
        if (node == nullptr) return nullptr;

        FieldBytes *tmp;

        auto tmp_flags = Flags(ACC_PUBLIC);

        if (node->access_mod_list) {
            tmp_flags = *Flags::convertToFlags(node->access_mod_list);
        }

        switch (node->type) {

            case ClassExprType::const_class_type:
                for (auto i: node->const_decl_list->vector) {
                    tmp = fromConstDeclNode(i, tmp_flags, consts);
                }
                break;
            case ClassExprType::get_value_assign_class_type:

            case ClassExprType::get_value_class_type:
                auto tmp_name = ConstantValue::CreateUtf8(node->id, consts);

                auto tmp_type = ConstantValue::getConstantByString(consts, new string("RTL/Value;"))
                                ?: ConstantValue::CreateUtf8(new string("RTL/Value;"), consts);

                tmp = new FieldBytes(
                        *tmp_name,
                        *tmp_type,
                        tmp_flags,
                        consts
                );
                break;
        }

        return tmp;
    }

};


#endif //PHP_COMPILER_FIELDBYTES_H
