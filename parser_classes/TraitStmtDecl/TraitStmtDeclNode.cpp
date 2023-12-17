#include "TraitStmtDeclNode.hpp"

int TraitStmtDeclNode::GLOBAL_ID = 0;

std::string *TraitStmtDeclNode::idTag() const {
    auto* tmp = new std::string(std::string("TraitStmtDecl") + std::to_string(this->cur_id));
    return tmp;
}

TraitStmtDeclNode* TraitStmtDeclNode::CreateNode(std::string* id, ClassStmtList* stmt_list)
{
    TraitStmtDeclNode* tmp = new TraitStmtDeclNode();
    tmp->id = id;
    tmp->stmt_list = stmt_list;
    tmp->cur_id = TraitStmtDeclNode::GLOBAL_ID++;
    return tmp;
}