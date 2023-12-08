#include "CaseDefaultStmtNode.hpp"

CaseDefaultStmtNode* CaseDefaultStmtNode::CreateFromCaseStmt(ExprNode* expr, StmtList* stmtList)
{
    CaseDefaultStmtNode* tmp = new CaseDefaultStmtNode();
    tmp->expr = expr;
    tmp->stmtList = stmtList;
    tmp->type = CaseDefaultType::case_stmt;
    return tmp;
}

CaseDefaultStmtNode* CaseDefaultStmtNode::CreateFromDefaultStmt(StmtList* stmtList)
{
    CaseDefaultStmtNode* tmp = new CaseDefaultStmtNode();
    tmp->stmtList = stmtList;
    tmp->type = CaseDefaultType::default_stmt;
    return tmp;
}

CaseDefaultStmtNode* CaseDefaultStmtNode::CreateFromFinallyStmt(StmtList* stmtList)
{
    CaseDefaultStmtNode* tmp = new CaseDefaultStmtNode();
    tmp->stmtList = stmtList;
    tmp->type = CaseDefaultType::finally_stmt;
    return tmp;
}
