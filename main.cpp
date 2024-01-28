#include <cstdio>
#include <iostream>
#include "parser_classes/all_include.hpp"
#include "semantic/semantic.h"
#include "code_generation/bytes/ClassBytes.h"

extern StartNode *startNode;
extern string *file_name;

extern int lexer_main(FILE *file);

int main(int argc, char *argv[]) {
    FILE *file = nullptr;
    if (argc > 1) {
        file = fopen(argv[1], "r");
    }

    if (file == nullptr) {
        printf("File opening error");
        return 1;
    }

    file_name = new string(argv[1]);
    int lex_res = lexer_main(file);

    if (lex_res)
        return lex_res;

    printTreeGraph(startNode);

    GRAPH_STR += "}";
    file = fopen("graph.dot", "w");
    fputs(GRAPH_STR.c_str(), file);
    fclose(file);

    try {
        inspectGlobalScope(startNode);
    } catch (const runtime_error &error) {
        //Fatal errors
        cout << error.what() << endl;
    }

    //code generation
    vector<ConstantValue *> consts;
    auto name = string("Main"); //
    auto super = string("java/lang/Object"); //
    auto source = string("Main.java"); //
    auto init = string("<init>");
    auto voidDesc = string("()V");
    auto codeVec = vector<ValueAndBytes *>();
    ClassBytes a = ClassBytes(
            Flags(ACC_PUBLIC + ACC_SUPER),
            ConstantValue::CreateUtf8(&name, &consts),
            ConstantValue::CreateUtf8(&super, &consts),
            new SourceFileAttribute(ConstantValue::CreateUtf8(&source, &consts), &consts),
            &consts);
    auto classConst = a.createClassConst();
    auto superClassConst = a.createSuperClassConst();
//    a.addMethod(
//            new MethodBytes(
//                    Flags(ACC_PUBLIC),
//                    ConstantValue::CreateUtf8(&init, &consts),
//                    ConstantValue::CreateUtf8(&voidDesc, &consts),
//                    new CodeAttribute(
//                            2,
//                            2,
//                            &codeVec,
//                            &consts
//                    ),
//                    &consts
//            ));
    auto out = WriteBytesToFile("Main.class");
    auto classBytes = a.classToBytes();
    out.write(classBytes);
    out.close();

    return 0;
}