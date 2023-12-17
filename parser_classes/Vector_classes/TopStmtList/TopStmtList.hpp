#include <vector>
#include <string>

#ifndef TOP_STMT_LIST_H
#define TOP_STMT_LIST_H

#include "../../TopStmt/TopStmtNode.hpp"

class TopStmtNode;

extern std::string GRAPH_STR;

class TopStmtList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<TopStmtNode *> vector;

    static TopStmtList *CreateNode(TopStmtNode *node);

    std::string* idTag() const;
};

#endif