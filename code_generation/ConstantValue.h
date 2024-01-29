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
    C_Float = 4,
    C_String = 8,
    C_NameAndType = 12,
    C_Class = 7,
    C_FieldRef = 9,
    C_MethodRef = 10,
};

class ConstantValue {
private:
    ConstantType typeConst = C_Utf8;
    ValueAndBytes value{0, 0};
    // id константы в виде строки, для поиска
    string *id = new string();

public:
    ConstantValue() = default;

    ConstantType getTypeConst() const {
        return typeConst;
    }

    ValueAndBytes getValue() const {
        return value;
    }

    string *getIdString() const {
        return id;
    }

    static bool isContainsConst(vector<ConstantValue> &consts, ConstantValue &val) {
        return any_of(consts.cbegin(), consts.cend(),
                      [&val](auto var) { return var == val; });
    }

    static int getIdConst(vector<ConstantValue> &consts, ConstantValue searchValue) {
        for (int i = 0; i < consts.size(); i++) {
            if (searchValue == consts[i]) return i + 1;
        }

        return -1;
    }

    static int getIdConstByString(const vector<ConstantValue> &consts , string *id, ConstantType type = C_Utf8) {
        for (int i = 0; i < consts.size(); i++) {
            if (consts[i].typeConst == type && *consts[i].id == *id) return i + 1;
        }

        return -1;
    }

    static int getIdConstByStringAll(const vector<ConstantValue> &consts , string *id) {
        for (int i = 0; i < consts.size(); i++) {
            if (*consts[i].id == *id) return i + 1;
        }

        return -1;
    }

    static ConstantValue
    getConstantByString(const vector<ConstantValue>& consts, string *searchValue, ConstantType type = C_Utf8) {
        for (auto i: consts) {
            if (i.typeConst == type && *i.id == *searchValue) {
                return i;
            }
        }

        return {};
    }

    bool operator==(ConstantValue &other) {
        return typeConst == other.typeConst && value == other.value;
    }

    static ConstantValue CreateUtf8(string *value, vector<ConstantValue> consts) {
        auto constant = ConstantValue();
        constant.typeConst = C_Utf8;
        constant.value = ValueAndBytes(*value);
        constant.id = value;

        if (isContainsConst(consts, constant)) throw runtime_error("Const is already exist");
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue CreateClass(ConstantValue name, vector<ConstantValue> &consts) {
        if (name.getTypeConst() != C_Utf8) throw runtime_error("Name is not utf-8");

        auto constant = ConstantValue();
        *constant.id = *name.id;
        constant.typeConst = C_Class;
        constant.value = ValueAndBytes(getIdConst(consts, name), 2);
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue CreateNameAndType(const ConstantValue& name, const ConstantValue& descriptor,
                                            vector<ConstantValue> consts) {
        if (name.getTypeConst() != C_Utf8) throw runtime_error("Name is not utf-8");
        if (descriptor.getTypeConst() != C_Utf8) throw runtime_error("Descriptor is not utf-8");

        auto constant = ConstantValue();
        constant.typeConst = C_NameAndType;
        int idName = getIdConst(consts, name);
        int idDesc = getIdConst(consts, descriptor);
        *constant.id = *name.id + *descriptor.id;
        constant.value = ValueAndBytes((idName << 16) | idDesc, 4);
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue CreateMethodRef(ConstantValue classConst, ConstantValue nameAndType,
                                          vector<ConstantValue> consts) {
        if (classConst.getTypeConst() != C_Class) throw runtime_error("Class const is not Class type");
        if (nameAndType.getTypeConst() != C_NameAndType) throw runtime_error("Name&Type const is not N&T type");

        auto constant = ConstantValue();
        constant.typeConst = C_MethodRef;
        int idClass = getIdConst(consts, classConst);
        int idNameAndType = getIdConst(consts, nameAndType);
        constant.value = ValueAndBytes((idClass << 16) | idNameAndType, 4);
        *constant.id = *classConst.id + "." +
                        *nameAndType.id; // Чтобы искать по классу и имени, формат Class.method(descriptor)
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue CreateFieldRef(ConstantValue *classConst, ConstantValue *nameAndType,
                                         vector<ConstantValue> &consts ) {
        if (classConst->getTypeConst() != C_Class) throw runtime_error("Class const is not Class type");
        if (nameAndType->getTypeConst() != C_NameAndType) throw runtime_error("Name&Type const is not N&T type");

        auto constant = ConstantValue();
        constant.typeConst = C_FieldRef;
        int idClass = getIdConst(consts, *classConst);
        int idNameAndType = getIdConst(consts, *nameAndType);
        constant.value = ValueAndBytes((idClass << 16) | idNameAndType, 4);
        *constant.id = *classConst->id + "." + *nameAndType->id;
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue CreateInteger(int value, vector<ConstantValue> &consts ) {
        auto constant = ConstantValue();
        constant.typeConst = C_Integer;
        constant.value = ValueAndBytes(value, 4);
        *constant.id = to_string(value);
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue CreateFloat(float value, vector<ConstantValue> &consts ) {
        auto constant = ConstantValue();
        constant.typeConst = C_Float;
        constant.value = ValueAndBytes(value, 4);
        *constant.id = to_string(value);
        consts.push_back(constant);

        return constant;
    }

    static ConstantValue CreateString(ConstantValue string, vector<ConstantValue> &consts ) {
        if (string.getTypeConst() != C_Utf8) throw runtime_error("String is not utf-8");

        auto constant = ConstantValue();
        constant.typeConst = C_String;
        constant.value = ValueAndBytes(getIdConst(consts, string), 2);
        *constant.id = *string.id;
        consts.push_back(constant);

        return constant;
    }
};

#endif //PHP_COMPILER_CONSTANTVALUE_H
