#include "TraitStmtDeclNode.hpp"

TraitStmtDeclNode* TraitStmtDeclNode::CreateNode(std::string* id, ClassStmtList* stmt_list)
{
    TraitStmtDeclNode* tmp = new TraitStmtDeclNode();
    tmp->id = id;
    tmp->stmt_list = stmt_list;
    return tmp;
}