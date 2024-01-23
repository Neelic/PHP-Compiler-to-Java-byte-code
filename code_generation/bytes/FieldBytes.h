//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_FIELDBYTES_H
#define PHP_COMPILER_FIELDBYTES_H


#include "code_generation/ConstantValue.h"
#include "WriteBytesToFile.h"
#include "Flags.h"
#include "code_generation/ConstantValueAttribute.h"

class FieldBytes {
private:
    vector<ConstantValue *> consts;
    Flags flags;
    ConstantValue fieldName;
    ConstantValue descriptor;
    vector<ConstantValueAttribute *> attributes;
public:
    FieldBytes(ConstantValue &fieldName, ConstantValue &descriptor, Flags flags, vector<ConstantValue *> &consts) :
            descriptor(descriptor), fieldName(fieldName), flags(flags), consts(consts) {
        if (fieldName.getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Field name is not utf-8 type");
        if (descriptor.getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Descriptor is not utf-8 type");
    }

    FieldBytes(ConstantValue &fieldName, ConstantValue &descriptor, Flags flags,
               vector<ConstantValueAttribute *> &attributes, vector<ConstantValue *> &consts) :
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

    vector<ValueAndBytes *> fieldToBytes() {
        vector<ValueAndBytes *> res;
        ValueAndBytes flagsBytes = flags.flagToBytes();
        res.push_back(&flagsBytes);
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, fieldName), 2));
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, descriptor), 2));

        res.push_back(new ValueAndBytes((int) attributes.size(), 2));

        for (auto *attr: attributes) {
            auto attrBytes = attr->attributeToBytes();
            res.insert(res.end(), attrBytes.begin(), attrBytes.end());
        }

        return res;
    }
};


#endif //PHP_COMPILER_FIELDBYTES_H
