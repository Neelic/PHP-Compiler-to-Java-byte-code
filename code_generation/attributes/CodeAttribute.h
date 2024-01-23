//
// Created by Dan on 23.01.2024.
//

#ifndef PHP_COMPILER_CODEATTRIBUTE_H
#define PHP_COMPILER_CODEATTRIBUTE_H


#include "code_generation/ConstantValue.h"
#include "TableAttribute.h"

class CodeAttribute {
private:
    ConstantValue *name;
    int maxStack;
    int maxLocals;
    vector<ValueAndBytes *> code;
    vector<TableAttribute *> attributes;
    vector<ConstantValue *> consts;

    int getAttrLength() {
        int res = 12; //exclude first 6 bytes
        res += getCodeLength();
        for (auto table: attributes) {
            res += table->getAttributeLength();
        }

        return res;
    }

    int getCodeLength() {
        int res = 0;
        for (auto bytes: code) {
            res += bytes->getBytes();
        }

        return res;
    }

public:
    CodeAttribute(ConstantValue *name, int maxStack, int maxLocals, vector<ValueAndBytes *> &code,
                  vector<TableAttribute *> &attributes, vector<ConstantValue *> &consts)
            : name(name), maxStack(maxStack), maxLocals(maxLocals), code(code), attributes(attributes), consts(consts) {
        if (name->getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Name is not utf-8 type");
    }

    vector<ValueAndBytes *> attributeToBytes() {
        auto res = vector<ValueAndBytes *>();

        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *name), 2));
        res.push_back(new ValueAndBytes(getAttrLength(), 4));
        res.push_back(new ValueAndBytes(maxStack, 2));
        res.push_back(new ValueAndBytes(maxLocals, 2));

        res.push_back(new ValueAndBytes(getCodeLength(), 4));
        res.insert(res.end(), code.begin(), code.end());
        res.push_back(new ValueAndBytes((int) 0, 2));

        res.push_back(new ValueAndBytes((int) attributes.size(), 2));
        for (auto table: attributes) {
            auto tableBytes = table->attributeToBytes();
            res.insert(res.end(), tableBytes.begin(), tableBytes.end());
        }

        return res;
    }
};

#endif //PHP_COMPILER_CODEATTRIBUTE_H
