#include "IfStmtNode.hpp"

int IfStmtNode::GLOBAL_ID = 0;

std::string *IfStmtNode::idTag() const {
    auto* tmp = new std::string(std::string("IfStmt") + std::to_string(this->cur_id));
    return tmp;
}

IfStmtNode* IfStmtNode::CreateFromIfStmt(ExprNode* expr, StmtNode* stmt_main)
{
    IfStmtNode* tmp = new IfStmtNode();
    tmp->expr = expr;
    tmp->stmt_main = stmt_main;
    tmp->type = IfStmtType::only_if;
    tmp->cur_id = IfStmtNode::GLOBAL_ID++;
    return tmp;
}

IfStmtNode* IfStmtNode::CreateFromIfElseStmt(ExprNode* expr, StmtNode* stmt_main, StmtNode* stmt_else)
{
    IfStmtNode* tmp = new IfStmtNode();
    tmp->expr = expr;
    tmp->stmt_main = stmt_main;
    tmp->stmt_else = stmt_else;
    tmp->type = IfStmtType::if_else;
    tmp->cur_id = IfStmtNode::GLOBAL_ID++;
    return tmp;
}

IfStmtNode* IfStmtNode::CreateFromIfEndIfStmt(ExprNode* expr, StmtList* stmtList)
{
    IfStmtNode* tmp = new IfStmtNode();
    tmp->expr = expr;
    tmp->stmtListMain = stmtList;
    tmp->type = IfStmtType::end_if;
    tmp->cur_id = IfStmtNode::GLOBAL_ID++;
    return tmp;
}

IfStmtNode* IfStmtNode::CreateFromIfElseEndIfStmt(ExprNode* expr, StmtList* stmtListMain, StmtList* stmtListElse)
{
    IfStmtNode* tmp = new IfStmtNode();
    tmp->expr = expr;
    tmp->stmtListMain = stmtListMain;
    tmp->stmtListElse = stmtListElse;
    tmp->type = IfStmtType::if_else_endif;
    tmp->cur_id = IfStmtNode::GLOBAL_ID++;
    return tmp;
}