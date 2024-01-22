#include <cstdio>
#include <iostream>
#include "parser_classes/all_include.hpp"
#include "semantic/semantic.h"

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

    return 0;
}