#include "ForEachStmtNode.hpp"

ForEachStmtNode* ForEachStmtNode::CreateFromForeachStmt(ExprNode* expr_left, ExprNode* expr_right, StmtNode* stmt)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->stmt = stmt;
    tmp->type = ForEachStmtType::foreach_stmt_type;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromForeachRightArrowStmt(ExprNode* expr_left, ExprNode* expr_right, std::string id, StmtNode* stmt)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->id = id;
    tmp->stmt = stmt;
    tmp->type = ForEachStmtType::foreach_r_double_arrow_stmt_type;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromForeachRightArrowPointerStmt(ExprNode* expr_left, ExprNode* expr_right, std::string id, StmtNode* stmt)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->id = id;
    tmp->stmt = stmt;
    tmp->type = ForEachStmtType::foreach_r_double_arrow_pointer_stmt_type;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromEndForeachStmt(ExprNode* expr_left, ExprNode* expr_right, std::vector<StmtNode*>* stmtList)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->stmtList = stmtList;
    tmp->type = ForEachStmtType::end_foreach_stmt_type;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromEndForeachRightArrowStmt(ExprNode* expr_left, ExprNode* expr_right, std::string id, std::vector<StmtNode*>* stmtList)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->id = id;
    tmp->stmtList = stmtList;
    tmp->type = ForEachStmtType::end_foreach_r_double_arrow_stmt_type;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromEndForeachRightArrowPointerStmt(ExprNode* expr_left, ExprNode* expr_right, std::string id, std::vector<StmtNode*>* stmtList)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->id = id;
    tmp->stmtList = stmtList;
    tmp->type = ForEachStmtType::end_foreach_r_double_arrow_pointer_stmt_type;
    return tmp;
}