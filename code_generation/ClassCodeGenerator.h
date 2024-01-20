//
// Created by Dan on 20.01.2024.
//

#ifndef PHP_COMPILER_CLASSCODEGENERATOR_H
#define PHP_COMPILER_CLASSCODEGENERATOR_H

#include <vector>
#include "ValueAndBytes.h"
#include "ConstantValue.h"

class ClassCodeGenerator {
private:
    ValueAndBytes magicConst = ValueAndBytes(0xCAFEBABE, 4);
    ValueAndBytes versionClassFile = ValueAndBytes(0x00000041, 4);
    vector<string *> consts;
    string className;
    string parentClassName;
    Flags flags;
public:
    explicit ClassCodeGenerator(string &className, string &parentClassName, Flags flags = Flags{true, false, true}) {
        this->className = className;
        this->parentClassName = parentClassName;
        this->flags = flags;
    }

    void addConst(string *constName);

    void generateFieldDef(string &nameField, string &descriptor);

    void generateMethodDef();
};


#endif //PHP_COMPILER_CLASSCODEGENERATOR_H
