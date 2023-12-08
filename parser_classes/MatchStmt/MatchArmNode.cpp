#include "MatchArmNode.hpp"

MatchArmNode* MatchArmNode::CreateFromMatchArmStmt(ExprList* exprList, ExprNode* expr)
{
    MatchArmNode* tmp = new MatchArmNode();
    tmp->exprList = exprList;
    tmp->expr = expr;
    return tmp;
}

MatchArmNode* MatchArmNode::CreateFromDefaultArmStmt(ExprNode* expr)
{
    MatchArmNode* tmp = new MatchArmNode();
    tmp->expr = expr;
    return tmp;
}

MatchArmNode* MatchArmNode::CreateFromDefaultArmWithCommaStmt(ExprNode* expr)
{
    MatchArmNode* tmp = new MatchArmNode();
    tmp->expr = expr;
    return tmp;
}