#include "MatchStmtNode.hpp"

MatchStmtNode* MatchStmtNode::CreateFromMatchStmtNode(ExprNode* expr, std::vector<MatchStmtNode*>* matchList)
{
    MatchStmtNode* tmp = new MatchStmtNode();
    tmp->expr = expr;
    tmp->matchList = matchList;
    return tmp;
}
