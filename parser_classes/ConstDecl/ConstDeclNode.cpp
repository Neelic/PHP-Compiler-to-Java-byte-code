#include "ConstDeclNode.hpp"

ConstDeclNode* ConstDeclNode::CreateFromConstDeclaration(std::string* id, ExprNode* expr)
{
    ConstDeclNode* tmp = new ConstDeclNode();
    tmp->id = id;
    tmp->expr = expr;
    return tmp;
}