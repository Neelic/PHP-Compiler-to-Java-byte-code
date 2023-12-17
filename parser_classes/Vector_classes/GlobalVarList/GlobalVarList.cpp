#include "GlobalVarList.hpp"

int GlobalVarList::GLOBAL_ID = 0;

GlobalVarList *GlobalVarList::CreateNode(GlobalVarNode *node) {
    auto *tmp = new GlobalVarList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = GlobalVarList::GLOBAL_ID++;
    return tmp;
}

std::string *GlobalVarList::idTag() const {
    auto* tmp = new std::string(std::string("GlobalVarList") + std::to_string(this->cur_id));
    return tmp;
}

