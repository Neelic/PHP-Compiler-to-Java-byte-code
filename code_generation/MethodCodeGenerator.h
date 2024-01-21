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
    Flags flags;
    vector<ConstantValue *> consts;
    bool isAbstract;

public:
    MethodCodeGenerator(vector<ConstantValue *> &consts) {
        this->consts = consts;
    }
};


#endif //PHP_COMPILER_METHODCODEGENERATOR_H
