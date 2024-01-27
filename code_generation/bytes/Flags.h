//
// Created by Dan on 22.01.2024.
//

#ifndef PHP_COMPILER_FLAGS_H
#define PHP_COMPILER_FLAGS_H

#include "ValueAndBytes.h"
#include "ClassAccessModList.hpp"
#include "ClassAccessModNode.hpp"

enum CodeFlags {
    ACC_PUBLIC = 0x0001,
    ACC_PRIVATE = 0x0002,
    ACC_PROTECTED = 0x0004,
    ACC_STATIC = 0x0008,
    ACC_FINAL = 0x0010,
    ACC_SUPER = 0x0020,
    ACC_ABSTRACT = 0x0400
};

class Flags {
    unsigned int codeOfFlag;
public:
    explicit Flags(unsigned int codeOfFlag) : codeOfFlag(codeOfFlag) {}

    const ValueAndBytes *flagToBytes() const {
        int resFlag = (int) codeOfFlag;
        return new ValueAndBytes(resFlag, 2);
    }

    static Flags *convertToFlags(ClassAccessModList *accessMod) {
        if (accessMod == nullptr) return nullptr;
        unsigned int code = 0;

        for (auto &i: accessMod->vector) {
            switch (i->access_mod) {
                case ClassAccessMod::public_node:
                    code += ACC_PUBLIC;
                    break;
                case ClassAccessMod::protected_node:
                    code += ACC_PROTECTED;
                    break;
                case ClassAccessMod::private_node:
                    code += ACC_PRIVATE;
                    break;
                case ClassAccessMod::static_node:
                    code += ACC_STATIC;
                    break;
                case ClassAccessMod::final_node:
                    code += ACC_FINAL;
                    break;
                case ClassAccessMod::abstract_node:
                    code += ACC_ABSTRACT;
                    break;
                case ClassAccessMod::read_only_node:
                    code += ACC_FINAL;
                    break;
            }
        }

        auto tmp = new Flags(code);

        return tmp;
    }
};

#endif //PHP_COMPILER_FLAGS_H
