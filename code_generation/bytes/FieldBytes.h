//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_FIELDBYTES_H
#define PHP_COMPILER_FIELDBYTES_H


#include "code_generation/ConstantValue.h"

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
        if (!ConstantValue::isContainsConst(consts, fieldName)) consts.push_back(&fieldName);
        if (!ConstantValue::isContainsConst(consts, descriptor)) consts.push_back(&descriptor);
    }

    void setAttributes(vector<ConstantValue *> &attr) {
        attributes = attr;
    }

    ValueAndBytes fieldToBytes() {
        ValueAndBytes flag = flags.flagToBytes();
        ValueAndBytes name = ValueAndBytes(ConstantValue::getIdConst(consts, fieldName), 2);
        ValueAndBytes desc = ValueAndBytes(ConstantValue::getIdConst(consts, descriptor), 2);

        int countAttr = (int) attributes.size();
        ValueAndBytes countAttrBytes = ValueAndBytes(countAttr, 2);
        for (auto attr : attributes) {
            //TODO
        }
    }
};


#endif //PHP_COMPILER_FIELDBYTES_H
