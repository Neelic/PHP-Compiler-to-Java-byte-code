#include "TryStmtNode.hpp"

TryStmtNode* TryStmtNode::CreateFromTryStmt(std::vector<StmtNode*>* stmtList)
{
    TryStmtNode* tmp = new TryStmtNode();
    tmp->stmtList = stmtList;
    return tmp;
}