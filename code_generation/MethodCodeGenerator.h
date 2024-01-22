//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_METHODCODEGENERATOR_H
#define PHP_COMPILER_METHODCODEGENERATOR_H

#include "string"
#include "ConstantValue.h"

class MethodCodeGenerator {
private:
    string methodName;
    Flags flags = Flags(ACC_PUBLIC + ACC_FINAL);
    vector<ConstantValue *> consts;
    bool isAbstract = false;

public:
    explicit MethodCodeGenerator(vector<ConstantValue *> &consts) {
        this->consts = consts;
    }
};


#endif //PHP_COMPILER_METHODCODEGENERATOR_H
