#include "FunctionDefNode.hpp"

int FunctionDefNode::GLOBAL_ID = 0;

std::string *FunctionDefNode::idTag() const {
    auto *tmp = new std::string(std::string("FunctionDef") + std::to_string(this->cur_id));
    return tmp;
}

FunctionDefNode *FunctionDefNode::CreateFromDefWithNoType(std::string *func_id, ExprFuncList *expr_func_list) {
    auto *tmp = new FunctionDefNode();
    tmp->func_id = func_id;
    if (expr_func_list == nullptr) expr_func_list = new ExprFuncList();
    tmp->expr_func_list = expr_func_list;
    tmp->type = FunctionDefType::no_type;
    tmp->cur_id = FunctionDefNode::GLOBAL_ID++;
    return tmp;
}

FunctionDefNode *
FunctionDefNode::CreateFromDefWithType(std::string *func_id, ExprFuncList *expr_func_list, std::string *type_id) {
    auto *tmp = new FunctionDefNode();
    tmp->func_id = func_id;
    if (expr_func_list == nullptr) expr_func_list = new ExprFuncList();
    tmp->expr_func_list = expr_func_list;
    tmp->type_id = type_id;
    tmp->type = FunctionDefType::with_type;
    tmp->cur_id = FunctionDefNode::GLOBAL_ID++;
    return tmp;
}