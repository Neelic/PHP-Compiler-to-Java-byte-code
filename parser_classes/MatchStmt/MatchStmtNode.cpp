#include "MatchStmtNode.hpp"

int MatchStmtNode::GLOBAL_ID = 0;

std::string MatchStmtNode::IdTag() {
    return std::string("MatchStmt") + std::to_string(this->cur_id);
}

MatchStmtNode* MatchStmtNode::CreateFromMatchStmtNode(ExprNode* expr, MatchArmList* matchList)
{
    MatchStmtNode* tmp = new MatchStmtNode();
    tmp->expr = expr;
    tmp->matchList = matchList;
    tmp->cur_id = MatchStmtNode::GLOBAL_ID++;
    return tmp;
}
