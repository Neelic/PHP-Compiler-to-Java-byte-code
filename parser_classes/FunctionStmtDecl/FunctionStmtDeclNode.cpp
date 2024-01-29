#include "FunctionStmtDeclNode.hpp"

int FunctionStmtDeclNode::GLOBAL_ID = 0;

std::string *FunctionStmtDeclNode::idTag() const {
    auto *tmp = new std::string(std::string("FunctionStmtDecl") + std::to_string(this->cur_id));
    return tmp;
}

FunctionStmtDeclNode *FunctionStmtDeclNode::CreateNode(FunctionDefNode *function_def, StmtList *stmt_list) {
    auto *tmp = new FunctionStmtDeclNode();
    tmp->function_def = function_def;
    if (stmt_list == nullptr) stmt_list = new StmtList();
    tmp->stmt_list = stmt_list;
    tmp->cur_id = FunctionStmtDeclNode::GLOBAL_ID++;
    return tmp;
}