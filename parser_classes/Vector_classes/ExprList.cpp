#include "ExprList.hpp"

int ExprList::GLOBAL_ID = 0;

ExprList *ExprList::CreateNode(ExprNode *node) {
    auto *tmp = new ExprList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = ExprList::GLOBAL_ID++;
    return tmp;
}
