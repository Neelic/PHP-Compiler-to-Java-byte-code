#include "TryStmtNode.hpp"

TryStmtNode* TryStmtNode::CreateFromTryStmt(std::vector<StmtList*>* stmtList)
{
    TryStmtNode* tmp = new TryStmtNode();
    tmp->stmtList = stmtList;
    return tmp;
}