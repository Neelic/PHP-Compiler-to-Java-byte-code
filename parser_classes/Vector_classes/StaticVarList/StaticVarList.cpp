#include "StaticVarList.hpp"

int StaticVarList::GLOBAL_ID = 0;

StaticVarList *StaticVarList::CreateNode(StaticVarNode *node) {
    auto *tmp = new StaticVarList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = StaticVarList::GLOBAL_ID++;
    return tmp;
}

std::string StaticVarList::IdTag() const {
    return std::string("StaticVarList") + std::to_string(this->cur_id);
}