#include "ExprFuncList.hpp"

int ExprFuncList::GLOBAL_ID = 0;

ExprFuncList *ExprFuncList::CreateNode(ExprFuncNode *node) {
    auto *tmp = new ExprFuncList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = ExprFuncList::GLOBAL_ID++;
    return tmp;
}

