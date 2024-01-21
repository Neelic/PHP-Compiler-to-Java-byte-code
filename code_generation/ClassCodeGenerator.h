//
// Created by Dan on 20.01.2024.
//

#ifndef PHP_COMPILER_CLASSCODEGENERATOR_H
#define PHP_COMPILER_CLASSCODEGENERATOR_H

#include <vector>
#include "code_generation/bytes/ValueAndBytes.h"
#include "ConstantValue.h"
#include "MethodCodeGenerator.h"
#include "code_generation/bytes/ClassBytes.h"

class ClassCodeGenerator {
private:
    vector<ConstantValue *> consts;
    string className;
    string parentClassName;
    Flags flags;
public:
    const MethodCodeGenerator methodCodeGenerator = MethodCodeGenerator(consts);
    const ClassBytes bytes = ClassBytes(consts);

    void addConst(ConstantValue &constName);

    void generateFieldDef(string &nameField, string &descriptor);

    void generateMethodDef();
};

#endif //PHP_COMPILER_CLASSCODEGENERATOR_H
