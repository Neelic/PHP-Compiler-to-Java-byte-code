#include "ConstDeclNode.hpp"

int ConstDeclNode::GLOBAL_ID = 0;

std::string *ConstDeclNode::idTag() const {
    auto* tmp = new std::string(std::string("ConstDecl") + std::to_string(this->cur_id));
    return tmp;
}

ConstDeclNode* ConstDeclNode::CreateFromConstDeclaration(std::string* id, ExprNode* expr)
{
    ConstDeclNode* tmp = new ConstDeclNode();
    tmp->id = id;
    tmp->expr = expr;
    tmp->cur_id = ConstDeclNode::GLOBAL_ID++;
    return tmp;
}