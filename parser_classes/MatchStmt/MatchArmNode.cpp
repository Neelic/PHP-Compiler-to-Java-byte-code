#include "MatchArmNode.hpp"

int MatchArmNode::GLOBAL_ID = 0;

std::string MatchArmNode::IdTag() {
    return std::string("MatchArm") + std::to_string(this->cur_id);
}

MatchArmNode* MatchArmNode::CreateFromMatchArmStmt(ExprList* exprList, ExprNode* expr)
{
    MatchArmNode* tmp = new MatchArmNode();
    tmp->exprList = exprList;
    tmp->expr = expr;
    tmp->cur_id = MatchArmNode::GLOBAL_ID++;
    return tmp;
}

MatchArmNode* MatchArmNode::CreateFromDefaultArmStmt(ExprNode* expr)
{
    MatchArmNode* tmp = new MatchArmNode();
    tmp->expr = expr;
    tmp->cur_id = MatchArmNode::GLOBAL_ID++;
    return tmp;
}

MatchArmNode* MatchArmNode::CreateFromDefaultArmWithCommaStmt(ExprNode* expr)
{
    MatchArmNode* tmp = new MatchArmNode();
    tmp->expr = expr;
    tmp->cur_id = MatchArmNode::GLOBAL_ID++;
    return tmp;
}