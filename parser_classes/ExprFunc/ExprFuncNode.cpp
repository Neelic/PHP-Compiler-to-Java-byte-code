#include "ExprFuncNode.hpp"

int ExprFuncNode::GLOBAL_ID = 0;

std::string *ExprFuncNode::idTag() const {
    auto* tmp = new std::string(std::string("ExprFunc") + std::to_string(this->cur_id));
    return tmp;
}

ExprFuncNode* ExprFuncNode::CreateFromGetValueFunc(GetValueFuncNode* get_value_func)
{
    ExprFuncNode* tmp = new ExprFuncNode();
    tmp->get_value_func = get_value_func;
    tmp->type = ExprFuncType::get_value_expr_type;
    tmp->cur_id = ExprFuncNode::GLOBAL_ID++;
    return tmp;
}

ExprFuncNode* ExprFuncNode::CreateFromGetValueFuncAssign(GetValueFuncNode* get_value_func, ExprNode* expr)
{
    ExprFuncNode* tmp = new ExprFuncNode();
    tmp->get_value_func = get_value_func;
    tmp->expr = expr;
    tmp->type = ExprFuncType::get_value_assign_expr_type;
    tmp->cur_id = ExprFuncNode::GLOBAL_ID++;
    return tmp;
}