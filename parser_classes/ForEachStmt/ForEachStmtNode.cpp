#include "ForEachStmtNode.hpp"

int ForEachStmtNode::GLOBAL_ID = 0;

std::string *ForEachStmtNode::idTag() const {
    auto* tmp = new std::string(std::string("ForEachStmt") + std::to_string(this->cur_id));
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromForeachStmt(ExprNode* expr_left, ExprNode* expr_right, StmtNode* stmt)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->stmt = stmt;
    tmp->type = ForEachStmtType::foreach_stmt_type;
    tmp->cur_id = ForEachStmtNode::GLOBAL_ID++;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromForeachRightArrowStmt(ExprNode* expr_left, ExprNode* expr_right, std::string* id, StmtNode* stmt)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->id = id;
    tmp->stmt = stmt;
    tmp->type = ForEachStmtType::foreach_r_double_arrow_stmt_type;
    tmp->cur_id = ForEachStmtNode::GLOBAL_ID++;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromForeachRightArrowPointerStmt(ExprNode* expr_left, ExprNode* expr_right, std::string* id, StmtNode* stmt)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->id = id;
    tmp->stmt = stmt;
    tmp->type = ForEachStmtType::foreach_r_double_arrow_pointer_stmt_type;
    tmp->cur_id = ForEachStmtNode::GLOBAL_ID++;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromEndForeachStmt(ExprNode* expr_left, ExprNode* expr_right, StmtList* stmtList)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->stmtList = stmtList;
    tmp->type = ForEachStmtType::end_foreach_stmt_type;
    tmp->cur_id = ForEachStmtNode::GLOBAL_ID++;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromEndForeachRightArrowStmt(ExprNode* expr_left, ExprNode* expr_right, std::string* id, StmtList* stmtList)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->id = id;
    tmp->stmtList = stmtList;
    tmp->type = ForEachStmtType::end_foreach_r_double_arrow_stmt_type;
    tmp->cur_id = ForEachStmtNode::GLOBAL_ID++;
    return tmp;
}

ForEachStmtNode* ForEachStmtNode::CreateFromEndForeachRightArrowPointerStmt(ExprNode* expr_left, ExprNode* expr_right, std::string* id, StmtList* stmtList)
{
    ForEachStmtNode* tmp = new ForEachStmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->id = id;
    tmp->stmtList = stmtList;
    tmp->type = ForEachStmtType::end_foreach_r_double_arrow_pointer_stmt_type;
    tmp->cur_id = ForEachStmtNode::GLOBAL_ID++;
    return tmp;
}