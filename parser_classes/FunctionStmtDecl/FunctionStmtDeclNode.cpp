#include "FunctionStmtDeclNode.hpp"

FunctionStmtDeclNode* FunctionStmtDeclNode::Create(FunctionDefNode* function_def, std::vector<StmtNode*>* stmt_list)
{
    FunctionStmtDeclNode* tmp = new FunctionStmtDeclNode();
    tmp->function_def = function_def;
    tmp->stmt_list = stmt_list;
    return tmp;
}