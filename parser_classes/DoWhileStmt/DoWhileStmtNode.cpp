#include "DoWhileStmtNode.hpp"

int DoWhileStmtNode::GLOBAL_ID = 0;

std::string DoWhileStmtNode::IdTag() {
    return std::string("DoWhileStmt") + std::to_string(this->cur_id);
}

DoWhileStmtNode* DoWhileStmtNode::CreateFromDoWhileStmt(StmtNode* stmt, ExprNode* expr)
{
    DoWhileStmtNode* tmp = new DoWhileStmtNode();
    tmp->stmt = stmt;
    tmp->expr = expr;
    tmp->cur_id = DoWhileStmtNode::GLOBAL_ID++;
    return tmp;
}
