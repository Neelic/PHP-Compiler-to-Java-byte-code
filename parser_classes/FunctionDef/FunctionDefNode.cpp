#include "FunctionDefNode.hpp"

FunctionDefNode* FunctionDefNode::CreateFromDefWithNoType(std::string* func_id, std::vector<ExprFuncNode*>* expr_func_list)
{
    FunctionDefNode* tmp = new FunctionDefNode();
    tmp->func_id = func_id;
    tmp->expr_func_list = expr_func_list;
    tmp->type = FunctionDefType::no_type;
    return tmp;
}

FunctionDefNode* FunctionDefNode::CreateFromDefWithType(std::string* func_id, std::vector<ExprFuncNode*>* expr_func_list, std::string* type_id)
{
    FunctionDefNode* tmp = new FunctionDefNode();
    tmp->func_id = func_id;
    tmp->expr_func_list = expr_func_list;
    tmp->type_id = type_id;
    tmp->type = FunctionDefType::with_type;
    return tmp;
}