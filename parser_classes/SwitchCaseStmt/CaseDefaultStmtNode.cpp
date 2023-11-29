#include "CaseDefaultStmtNode.hpp"

CaseDefaultStmtNode* CaseDefaultStmtNode::CreateFromCaseStmt(ExprNode* expr, std::vector<StmtNode*>* stmtList)
{
    CaseDefaultStmtNode* tmp = new CaseDefaultStmtNode();
    tmp->expr = expr;
    tmp->stmtList = stmtList;
    tmp->type = CaseDefaultType::case_stmt;
    return tmp;
}

CaseDefaultStmtNode* CaseDefaultStmtNode::CreateFromDefaultStmt(std::vector<StmtNode*>* stmtList)
{
    CaseDefaultStmtNode* tmp = new CaseDefaultStmtNode();
    tmp->stmtList = stmtList;
    tmp->type = CaseDefaultType::default_stmt;
    return tmp;
}

CaseDefaultStmtNode* CaseDefaultStmtNode::CreateFromFinallyStmt(std::vector<StmtNode*>* stmtList)
{
    CaseDefaultStmtNode* tmp = new CaseDefaultStmtNode();
    tmp->stmtList = stmtList;
    tmp->type = CaseDefaultType::finally_stmt;
    return tmp;
}
