#include "ForStmtNode.hpp"

ForStmtNode* ForStmtNode::CreateFromForStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, StmtNode* stmt)
{
    ForStmtNode* tmp = new ForStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_central = expr_central;
    tmp->expr_right = expr_right;
    tmp->stmt = stmt;
    tmp->type = ForStmtType::for_stmt;
    return tmp;
}

ForStmtNode* ForStmtNode::CreateFromForEndStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, std::vector<StmtNode*>* stmtList)
{
    ForStmtNode* tmp = new ForStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_central = expr_central;
    tmp->expr_right = expr_right;
    tmp->stmtList = stmtList;
    tmp->type = ForStmtType::for_end_stmt;
    return tmp;
}