#include "ForStmtNode.hpp"

int ForStmtNode::GLOBAL_ID = 0;

std::string ForStmtNode::IdTag() {
    return std::string("ForStmt") + std::to_string(this->cur_id);
}

ForStmtNode* ForStmtNode::CreateFromForStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, StmtNode* stmt)
{
    ForStmtNode* tmp = new ForStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_central = expr_central;
    tmp->expr_right = expr_right;
    tmp->stmt = stmt;
    tmp->type = ForStmtType::for_stmt_type;
    tmp->cur_id = ForStmtNode::GLOBAL_ID++;
    return tmp;
}

ForStmtNode* ForStmtNode::CreateFromForEndStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, StmtList* stmtList)
{
    ForStmtNode* tmp = new ForStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_central = expr_central;
    tmp->expr_right = expr_right;
    tmp->stmtList = stmtList;
    tmp->type = ForStmtType::for_end_stmt_type;
    tmp->cur_id = ForStmtNode::GLOBAL_ID++;
    return tmp;
}