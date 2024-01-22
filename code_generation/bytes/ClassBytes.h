//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_CLASSBYTES_H
#define PHP_COMPILER_CLASSBYTES_H


#include "ValueAndBytes.h"
#include "code_generation/ConstantValue.h"
#include "FieldBytes.h"

class ClassBytes {
private:
    static ValueAndBytes magicConst;
    static ValueAndBytes versionClassFile;

    vector<ConstantValue *> consts;
    vector<FieldBytes *> fields;

public:
    ClassBytes(vector<ConstantValue *> &consts) {
        this->consts = consts;
    }

    void addField(FieldBytes *field) {}

    ValueAndBytes classToBytes() {
        return ValueAndBytes(1);
    }
};

ValueAndBytes ClassBytes::magicConst = ValueAndBytes(0xCAFEBABE, 4);
ValueAndBytes ClassBytes::versionClassFile = ValueAndBytes(0x00000041, 4);

#endif //PHP_COMPILER_CLASSBYTES_H
