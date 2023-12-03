#include "InterfaceStmtDeclNode.hpp"

InterfaceStmtDeclNode* InterfaceStmtDeclNode::Create(InterfaceExprDefNode* expr_definition, std::vector<InterfaceStmtNode*>* stmt_list)
{
    InterfaceStmtDeclNode* tmp = new InterfaceStmtDeclNode();
    tmp->expr_definition = expr_definition;
    tmp->stmt_list = stmt_list;
    return tmp;
}