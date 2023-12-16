#include "ConstDeclNode.hpp"

int ConstDeclNode::GLOBAL_ID = 0;

std::string ConstDeclNode::IdTag() {
    return std::string("ConstDecl") + std::to_string(this->cur_id);
}

ConstDeclNode* ConstDeclNode::CreateFromConstDeclaration(std::string* id, ExprNode* expr)
{
    ConstDeclNode* tmp = new ConstDeclNode();
    tmp->id = id;
    tmp->expr = expr;
    tmp->cur_id = ConstDeclNode::GLOBAL_ID++;
    return tmp;
}