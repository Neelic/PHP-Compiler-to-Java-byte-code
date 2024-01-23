//
// Created by Dan on 20.01.2024.
//

#ifndef PHP_COMPILER_CONSTANTVALUE_H
#define PHP_COMPILER_CONSTANTVALUE_H

#include <vector>
#include <algorithm>
#include "code_generation/bytes/ValueAndBytes.h"

enum ConstantType {
    C_Utf8 = 1,
    C_Integer = 3,
    C_String = 8,
    C_NameAndType = 12,
    C_Class = 7,
    C_FieldRef = 9,
    C_MethodRef = 10,
};

class ConstantValue {
private:
    ConstantType typeConst = C_Utf8;
    ValueAndBytes *value = nullptr;

    ConstantValue() {}
public:
    ConstantType getTypeConst() const {
        return typeConst;
    }

    ValueAndBytes *getValue() const {
        return value;
    }

    static bool isContainsConst(vector<ConstantValue *> &consts, ConstantValue &val) {
        return any_of(consts.cbegin(), consts.cend(),
                      [&val](auto var) { return *var == val; });
    }

    static int getIdConst(vector<ConstantValue *> &consts, ConstantValue &searchValue) {
        for (int i = 0; i < consts.size(); i++) {
            if (searchValue == *consts[i]) return i + 1;
        }

        return -1;
    }

    bool operator==(ConstantValue other) {
        return typeConst == other.typeConst && (string(value->getValue()) == string(other.value->getValue()) &&
                                                value->getBytes() == other.value->getBytes());
    }

    static ConstantValue *CreateUtf8(string &value, vector<ConstantValue *> &consts) {
        auto *constant = new ConstantValue();
        constant->typeConst = C_Utf8;
        constant->value = new ValueAndBytes(value.c_str(), (int) value.length());

        if (isContainsConst(consts, *constant)) throw runtime_error("Const is already exist");
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue *CreateClass(ConstantValue *name, vector<ConstantValue *> &consts) {
        if (name->getTypeConst() != C_Utf8) throw runtime_error("Name is not utf-8");

        auto constant = new ConstantValue;
        constant->typeConst = C_Class;
        constant->value = new ValueAndBytes(getIdConst(consts, *name), 2);
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue *CreateNameAndType(ConstantValue *name, ConstantValue *descriptor,
                                            vector<ConstantValue *> &consts) {
        if (name->getTypeConst() != C_Utf8) throw runtime_error("Name is not utf-8");
        if (descriptor->getTypeConst() != C_Utf8) throw runtime_error("Descriptor is not utf-8");

        auto constant = new ConstantValue;
        constant->typeConst = C_NameAndType;
        int idName = getIdConst(consts, *name);
        int idDesc = getIdConst(consts, *descriptor);
        constant->value = new ValueAndBytes((idName << 16) | idDesc, 4);
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue *CreateMethodRef(ConstantValue *classConst, ConstantValue *nameAndType,
                                          vector<ConstantValue *> &consts) {
        if (classConst->getTypeConst() != C_Class) throw runtime_error("Class const is not Class type");
        if (nameAndType->getTypeConst() != C_NameAndType) throw runtime_error("Name&Type const is not N&T type");

        auto constant = new ConstantValue;
        constant->typeConst = C_MethodRef;
        int idClass = getIdConst(consts, *classConst);
        int idNameAndType = getIdConst(consts, *nameAndType);
        constant->value = new ValueAndBytes((idClass << 16) | idNameAndType, 4);
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue *CreateFieldRef(ConstantValue *classConst, ConstantValue *nameAndType,
                                         vector<ConstantValue *> &consts) {
        if (classConst->getTypeConst() != C_Class) throw runtime_error("Class const is not Class type");
        if (nameAndType->getTypeConst() != C_NameAndType) throw runtime_error("Name&Type const is not N&T type");

        auto constant = new ConstantValue;
        constant->typeConst = C_FieldRef;
        int idClass = getIdConst(consts, *classConst);
        int idNameAndType = getIdConst(consts, *nameAndType);
        constant->value = new ValueAndBytes((idClass << 16) | idNameAndType, 4);
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue *CreateInteger(int value, vector<ConstantValue *> &consts) {
        auto constant = new ConstantValue;
        constant->typeConst = C_Integer;
        constant->value = new ValueAndBytes(value, 4);
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue *CreateString(ConstantValue *string, vector<ConstantValue *> &consts) {
        if (string->getTypeConst() != C_Utf8) throw runtime_error("String is not utf-8");

        auto constant = new ConstantValue;
        constant->typeConst = C_String;
        constant->value = new ValueAndBytes(getIdConst(consts, *string), 2);
        consts.push_back(constant);

        return constant;
    }
};

#endif //PHP_COMPILER_CONSTANTVALUE_H
