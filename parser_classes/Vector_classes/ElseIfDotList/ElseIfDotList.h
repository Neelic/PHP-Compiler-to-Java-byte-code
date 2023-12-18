#ifndef PHP_COMPILER_ELSE_IF_DOT_LIST_H
#define PHP_COMPILER_ELSE_IF_DOT_LIST_H
#include <vector>

class IfStmtNode;

class ElseIfDotList {
public:
    std::vector<IfStmtNode*> vector;
    int cur_id = 0;
    static int GLOBAL_ID;

    static ElseIfDotList *Create(IfStmtNode* node);
};


#endif //PHP_COMPILER_ELSE_IF_DOT_LIST_H
