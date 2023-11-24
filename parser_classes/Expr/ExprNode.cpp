#include "ExprNode.hpp"

ExprNode* ExprNode::CreateFromId(std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->id = id;
    tmp->exprType = constant;
    return tmp;
}

ExprNode *ExprNode::CreateFromFunctionCall(std::string* id, std::vector<ExprNode*>* listParams)
{
    return nullptr;
}
