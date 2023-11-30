#include "DoWhileStmtNode.hpp"

DoWhileStmtNode* DoWhileStmtNode::CreateFromDoWhileStmt(StmtNode* stmt, ExprNode* expr)
{
    DoWhileStmtNode* tmp = new DoWhileStmtNode();
    tmp->stmt = stmt;
    tmp->expr = expr;
    return tmp;
}
