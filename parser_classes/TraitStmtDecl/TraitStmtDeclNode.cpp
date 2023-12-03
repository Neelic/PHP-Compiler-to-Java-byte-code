#include "TraitStmtDeclNode.hpp"

TraitStmtDeclNode* TraitStmtDeclNode::Create(std::string* id, std::vector<ClassStmtNode*>* stmt_list)
{
    TraitStmtDeclNode* tmp = new TraitStmtDeclNode();
    tmp->id = id;
    tmp->stmt_list = stmt_list;
    return tmp;
}