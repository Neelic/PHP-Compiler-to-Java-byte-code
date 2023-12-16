#include "GlobalVarList.hpp"

int GlobalVarList::GLOBAL_ID = 0;

GlobalVarList *GlobalVarList::CreateNode(GlobalVarNode *node) {
    auto *tmp = new GlobalVarList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = GlobalVarList::GLOBAL_ID++;
    return tmp;
}

