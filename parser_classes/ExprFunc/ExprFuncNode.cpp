#include "ExprFuncNode.hpp"

ExprFuncNode* ExprFuncNode::CreateFromGetValueFunc(GetValueFuncNode* get_value_func)
{
    ExprFuncNode* tmp = new ExprFuncNode();
    tmp->get_value_func = get_value_func;
    tmp->type = ExprFuncType::get_value_expr_type;
    return tmp;
}

ExprFuncNode* ExprFuncNode::CreateFromGetValueFuncAssign(GetValueFuncNode* get_value_func, ExprNode* expr)
{
    ExprFuncNode* tmp = new ExprFuncNode();
    tmp->get_value_func = get_value_func;
    tmp->expr = expr;
    tmp->type = ExprFuncType::get_value_assign_expr_type;
    return tmp;
}