#ifndef PHP_COMPILER_STMT_LIST_NODE
#define PHP_COMPILER_STMT_LIST_NODE

#include <vector>

class StmtNode;

#include <string>

class StmtList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<StmtNode *> vector;

    static StmtList *CreateNode(StmtNode *node);

    std::string* idTag() const;
};

#endif
