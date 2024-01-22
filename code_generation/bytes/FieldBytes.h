//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_FIELDBYTES_H
#define PHP_COMPILER_FIELDBYTES_H


#include "code_generation/ConstantValue.h"
#include "WriteBytesToFile.h"
#include "Flags.h"

class FieldBytes {
private:
    vector<ConstantValue *> consts;
    Flags flags;
    ConstantValue fieldName;
    ConstantValue descriptor;
    vector<ConstantValue *> attributes;
public:
    FieldBytes(ConstantValue &fieldName, ConstantValue &descriptor, Flags flags, vector<ConstantValue *> &consts) :
            descriptor(descriptor), fieldName(fieldName), flags(flags), consts(consts) {
        if (fieldName.getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Field name is not utf-8 type");
        if (descriptor.getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Descriptor is not utf-8 type");
        if (!ConstantValue::isContainsConst(consts, fieldName)) consts.push_back(&fieldName);
        if (!ConstantValue::isContainsConst(consts, descriptor)) consts.push_back(&descriptor);
    }

    void setAttributes(vector<ConstantValue *> &attr) {
        attributes = attr;
    }

    void addAttribute(ConstantValue &attr) {
        attributes.push_back(&attr);
    }

    vector<ValueAndBytes *> fieldToBytes() {
        vector<ValueAndBytes *> res;
        ValueAndBytes flagsBytes = flags.flagToBytes();
        res.push_back(&flagsBytes);
        ValueAndBytes nameBytes = ValueAndBytes(ConstantValue::getIdConst(consts, fieldName), 2);
        res.push_back(&nameBytes);
        ValueAndBytes descBytes = ValueAndBytes(ConstantValue::getIdConst(consts, descriptor), 2);
        res.push_back(&descBytes);

        int countAttr = (int) attributes.size();
        ValueAndBytes countAttrBytes = ValueAndBytes(countAttr, 2);
        res.push_back(&countAttrBytes);

        for (auto *attr: attributes) {
            res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *attr), 2));
            res.push_back(new ValueAndBytes(2, 4));
            res.push_back(new ValueAndBytes(2));
        }

        return res;
    }
};


#endif //PHP_COMPILER_FIELDBYTES_H
