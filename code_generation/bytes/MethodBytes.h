//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_METHODBYTES_H
#define PHP_COMPILER_METHODBYTES_H


#include "Flags.h"
#include "code_generation/ConstantValue.h"
#include "code_generation/attributes/CodeAttribute.h"

class MethodBytes {
private:
    Flags flags;
    ConstantValue *name;
    ConstantValue *descriptor;
    CodeAttribute *code;
    vector<ConstantValue *> consts;

public:
    MethodBytes(Flags &flags, ConstantValue *name, ConstantValue *descriptor, CodeAttribute *code,
                vector<ConstantValue *> &consts) :
            flags(flags), name(name), descriptor(descriptor), code(code), consts(consts) {
        if (name->getTypeConst() != C_Utf8) throw runtime_error("Name is not Utf-8");
        if (descriptor->getTypeConst() != C_Utf8) throw runtime_error("Descriptor is not Utf-8");
    }

    vector<ValueAndBytes *> methodToBytes() {
        auto res = vector<ValueAndBytes *>();

        auto flagsBytes = flags.flagToBytes();
        res.push_back(&flagsBytes);
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *name), 2));
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *descriptor), 2));
        res.push_back(new ValueAndBytes(1, 2));

        auto codeByteVector = code->attributeToBytes();
        res.insert(res.end(), codeByteVector.begin(), codeByteVector.end());

        return res;
    }
};


#endif //PHP_COMPILER_METHODBYTES_H
