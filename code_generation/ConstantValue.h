//
// Created by Dan on 20.01.2024.
//

#ifndef PHP_COMPILER_CONSTANTVALUE_H
#define PHP_COMPILER_CONSTANTVALUE_H

#include <vector>
#include "ValueAndBytes.h"

struct Flags {
    bool public_f = false;
    bool abstract_f = false;
    bool super_f = false;
    bool static_f = false;
    bool private_f = false;
    bool protected_f = false;
    bool final_f = false;
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
    vector<ConstantValue *> refs;
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

    const vector<ConstantValue *> &getRefs() const {
        return refs;
    }

    ConstantValue(ConstantType type, ValueAndBytes *value, Flags flags = Flags(),
                  const vector<ConstantValue *> &refs = vector<ConstantValue *>()) {
        this->value = value;
        this->typeConst = type;
        this->flags = flags;
        this->refs = refs;
    }
};

#endif //PHP_COMPILER_CONSTANTVALUE_H
