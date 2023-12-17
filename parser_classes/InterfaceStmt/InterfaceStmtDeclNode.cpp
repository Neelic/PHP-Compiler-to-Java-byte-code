#include "InterfaceStmtDeclNode.hpp"

int InterfaceStmtDeclNode::GLOBAL_ID = 0;

std::string *InterfaceStmtDeclNode::idTag() const {
    auto* tmp = new std::string(std::string("InterfaceStmtDecl") + std::to_string(this->cur_id));
    return tmp;
}

InterfaceStmtDeclNode* InterfaceStmtDeclNode::CreateNode(InterfaceExprDefNode* expr_definition, InterfaceStmtList* stmt_list)
{
    InterfaceStmtDeclNode* tmp = new InterfaceStmtDeclNode();
    tmp->expr_definition = expr_definition;
    tmp->stmt_list = stmt_list;
    tmp->cur_id = InterfaceStmtDeclNode::GLOBAL_ID++;
    return tmp;
}