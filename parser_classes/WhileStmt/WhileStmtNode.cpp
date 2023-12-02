#include "WhileStmtNode.hpp"

WhileStmtNode* WhileStmtNode::CreateFromWhileStmt(ExprNode* expr, StmtNode* stmt)
{
    WhileStmtNode* tmp = new WhileStmtNode();
    tmp->expr = expr;
    tmp->stmt = stmt;
    tmp->type = WhileStmtType::while_stmt_type;
    return tmp;
}

WhileStmtNode* WhileStmtNode::CreateFromEndWhileStmt(ExprNode* expr, std::vector<StmtNode*>* stmtList)
{
    WhileStmtNode* tmp = new WhileStmtNode();
    tmp->expr = expr;
    tmp->stmtList = stmtList;
    tmp->type = WhileStmtType::end_while_stmt_type;
    return tmp;
}
