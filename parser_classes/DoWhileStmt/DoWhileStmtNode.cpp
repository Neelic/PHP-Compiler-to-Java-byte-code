#include "DoWhileStmtNode.hpp"

int DoWhileStmtNode::GLOBAL_ID = 0;

std::string *DoWhileStmtNode::idTag() const {
    auto* tmp = new std::string(std::string("DoWhileStmt") + std::to_string(this->cur_id));
    return tmp;
}

DoWhileStmtNode* DoWhileStmtNode::CreateFromDoWhileStmt(StmtNode* stmt, ExprNode* expr)
{
    DoWhileStmtNode* tmp = new DoWhileStmtNode();
    tmp->stmt = stmt;
    tmp->expr = expr;
    tmp->cur_id = DoWhileStmtNode::GLOBAL_ID++;
    return tmp;
}
