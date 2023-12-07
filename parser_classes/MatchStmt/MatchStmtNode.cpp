#include "MatchStmtNode.hpp"

MatchStmtNode* MatchStmtNode::CreateFromMatchStmtNode(ExprNode* expr, MatchArmList* matchList)
{
    MatchStmtNode* tmp = new MatchStmtNode();
    tmp->expr = expr;
    tmp->matchList = matchList;
    return tmp;
}
