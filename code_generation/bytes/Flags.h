//
// Created by Dan on 22.01.2024.
//

#ifndef PHP_COMPILER_FLAGS_H
#define PHP_COMPILER_FLAGS_H

#include "ValueAndBytes.h"

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

#endif //PHP_COMPILER_FLAGS_H
