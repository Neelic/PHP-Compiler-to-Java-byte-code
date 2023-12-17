#include "WhileStmtNode.hpp"

int WhileStmtNode::GLOBAL_ID = 0;

std::string WhileStmtNode::IdTag() {
    return std::string("WhileStmt") + std::to_string(this->cur_id);
}

WhileStmtNode* WhileStmtNode::CreateFromWhileStmt(ExprNode* expr, StmtNode* stmt)
{
    WhileStmtNode* tmp = new WhileStmtNode();
    tmp->expr = expr;
    tmp->stmt = stmt;
    tmp->type = WhileStmtType::while_stmt_type;
    tmp->cur_id = WhileStmtNode::GLOBAL_ID++;
    return tmp;
}

WhileStmtNode* WhileStmtNode::CreateFromEndWhileStmt(ExprNode* expr, StmtList* stmtList)
{
    WhileStmtNode* tmp = new WhileStmtNode();
    tmp->expr = expr;
    tmp->stmtList = stmtList;
    tmp->type = WhileStmtType::end_while_stmt_type;
    tmp->cur_id = WhileStmtNode::GLOBAL_ID++;
    return tmp;
}
