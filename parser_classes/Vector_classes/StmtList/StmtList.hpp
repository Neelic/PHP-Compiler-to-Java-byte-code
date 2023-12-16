#include <vector>

class StmtNode;

#ifndef STMT_LIST_H
#define STMT_LIST_H

#include <string>

class StmtList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<StmtNode *> vector;

    static StmtList *CreateNode(StmtNode *node);

    std::string IdTag() const;
};

#endif