//
// Created by Dan on 20.01.2024.
//

#ifndef PHP_COMPILER_CONSTANTVALUE_H
#define PHP_COMPILER_CONSTANTVALUE_H

#include <vector>
#include <algorithm>
#include "code_generation/bytes/ValueAndBytes.h"

enum CodeFlags {
    ACC_PUBLIC = 0x0001,
    ACC_PRIVATE = 0x0002,
    ACC_PROTECTED = 0x0004,
    ACC_STATIC = 0x0008,
    ACC_FINAL = 0x0010,
    ACC_ABSTRACT = 0x0400
};

class Flags {
    unsigned int codeOfFlag;
public:
    explicit Flags(unsigned int codeOfFlag) : codeOfFlag(codeOfFlag) {}

    ValueAndBytes flagToBytes() const {
        return {codeOfFlag, 2};
    }
};

enum ConstantType {
    C_Utf8 = 1,
    C_Integer = 3,
    C_String = 8,
    C_NameAndType = 12,
    C_Class = 7,
    C_FieldRef = 9,
    C_MethodRef = 10,
    C_ConstantValue = 13,
};

class ConstantValue {
private:
    ConstantType typeConst;
    ValueAndBytes *value;
    Flags flags;
    vector<ConstantValue *> descriptors;
public:
    ConstantType getTypeConst() const {
        return typeConst;
    }

    ValueAndBytes *getValue() const {
        return value;
    }

    const Flags &getFlags() const {
        return flags;
    }

    const vector<ConstantValue *> &getDescriptors() const {
        return descriptors;
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

    ConstantValue(ConstantType type, ValueAndBytes *value, const Flags &flags = Flags(ACC_PUBLIC + ACC_FINAL),
                  const vector<ConstantValue *> &descriptors = vector<ConstantValue *>()) : typeConst(type),
                                                                                            value(value),
                                                                                            flags(flags),
                                                                                            descriptors(descriptors) {
    }

    bool operator==(ConstantValue other) {
        return typeConst == other.typeConst && (string(value->getValue()) == string(other.value->getValue()) &&
                                                value->getBytes() == other.value->getBytes());
    }
};

#endif //PHP_COMPILER_CONSTANTVALUE_H
