//
// Created by Dan on 23.01.2024.
//

#ifndef PHP_COMPILER_CONSTANTVALUEATTRIBUTE_H
#define PHP_COMPILER_CONSTANTVALUEATTRIBUTE_H

#include <string>
#include <vector>
#include "code_generation/ConstantValue.h"

using namespace std;

class ConstantValueAttribute {
private:
    ConstantValue *name;
    int bytesLength = 2;
    ConstantValue *value;
    vector<ConstantValue *> *consts;

public:
    ConstantValueAttribute(ConstantValue *name, ConstantValue *value, vector<ConstantValue *> *consts) {
        if (name->getTypeConst() != C_Utf8) throw runtime_error("Name is not Utf-8");
        if (value->getTypeConst() != C_Utf8) throw runtime_error("Value is not Utf-8");

        this->name = name;
        this->value = value;
        this->consts = consts;
    }

    vector<ValueAndBytes> attributeToBytes() {
        auto res = vector<ValueAndBytes>();
        res.emplace_back(ConstantValue::getIdConst(consts, *name), 2);
        res.emplace_back(bytesLength, 4);
        res.emplace_back(ConstantValue::getIdConst(consts, *value), 2);

        return res;
    }
};


#endif //PHP_COMPILER_CONSTANTVALUEATTRIBUTE_H
