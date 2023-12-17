#include "CaseDefaultStmtNode.hpp"

int CaseDefaultStmtNode::GLOBAL_ID = 0;

std::string CaseDefaultStmtNode::IdTag() {
    return std::string("CaseDefaultStmt") + std::to_string(this->cur_id);
}

CaseDefaultStmtNode* CaseDefaultStmtNode::CreateFromCaseStmt(ExprNode* expr, StmtList* stmtList)
{
    CaseDefaultStmtNode* tmp = new CaseDefaultStmtNode();
    tmp->expr = expr;
    tmp->stmtList = stmtList;
    tmp->type = CaseDefaultType::case_stmt;
    tmp->cur_id = CaseDefaultStmtNode::GLOBAL_ID++;
    return tmp;;
}

CaseDefaultStmtNode* CaseDefaultStmtNode::CreateFromDefaultStmt(StmtList* stmtList)
{
    CaseDefaultStmtNode* tmp = new CaseDefaultStmtNode();
    tmp->stmtList = stmtList;
    tmp->type = CaseDefaultType::default_stmt;
    tmp->cur_id = CaseDefaultStmtNode::GLOBAL_ID++;
    return tmp;;
}

CaseDefaultStmtNode* CaseDefaultStmtNode::CreateFromFinallyStmt(StmtList* stmtList)
{
    CaseDefaultStmtNode* tmp = new CaseDefaultStmtNode();
    tmp->stmtList = stmtList;
    tmp->type = CaseDefaultType::finally_stmt;
    tmp->cur_id = CaseDefaultStmtNode::GLOBAL_ID++;
    return tmp;;
}
