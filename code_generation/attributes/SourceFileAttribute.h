//
// Created by Dan on 23.01.2024.
//

#ifndef PHP_COMPILER_SOURCEFILEATTRIBUTE_H
#define PHP_COMPILER_SOURCEFILEATTRIBUTE_H


#include "code_generation/ConstantValue.h"

class SourceFileAttribute {
private:
    ConstantValue *nameAttr;
    ConstantValue *fileName;
    vector<ConstantValue *> consts;

public:
    SourceFileAttribute(ConstantValue *nameAttr, ConstantValue *fileName, vector<ConstantValue *> &consts)
            : nameAttr(nameAttr), fileName(fileName), consts(consts) {
        if (nameAttr->getTypeConst() != ConstantType::C_Utf8) throw runtime_error("Name is not utf-8 type");
        if (fileName->getTypeConst() != ConstantType::C_Utf8) throw runtime_error("File name is not utf-8 type");
    }

    vector<ValueAndBytes *> attributeToBytes() {
        auto res = vector<ValueAndBytes *>();

        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *nameAttr), 2));
        res.push_back(new ValueAndBytes(2, 4));
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *fileName), 2));

        return res;
    }

};


#endif //PHP_COMPILER_SOURCEFILEATTRIBUTE_H
