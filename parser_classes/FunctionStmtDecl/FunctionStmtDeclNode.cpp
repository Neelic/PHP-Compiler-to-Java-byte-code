#include "FunctionStmtDeclNode.hpp"

FunctionStmtDeclNode* FunctionStmtDeclNode::CreateNode(FunctionDefNode* function_def, StmtList* stmt_list)
{
    FunctionStmtDeclNode* tmp = new FunctionStmtDeclNode();
    tmp->function_def = function_def;
    tmp->stmt_list = stmt_list;
    return tmp;
}