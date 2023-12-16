#include "FunctionStmtDeclNode.hpp"

int FunctionStmtDeclNode::GLOBAL_ID = 0;

std::string FunctionStmtDeclNode::IdTag() {
    return std::string("FunctionStmtDecl") + std::to_string(this->cur_id);
}

FunctionStmtDeclNode* FunctionStmtDeclNode::CreateNode(FunctionDefNode* function_def, StmtList* stmt_list)
{
    FunctionStmtDeclNode* tmp = new FunctionStmtDeclNode();
    tmp->function_def = function_def;
    tmp->stmt_list = stmt_list;
    tmp->cur_id = FunctionStmtDeclNode::GLOBAL_ID++;
    return tmp;
}