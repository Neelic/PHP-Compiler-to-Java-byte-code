#include "MatchArmList.hpp"

int MatchArmList::GLOBAL_ID = 0;

MatchArmList *MatchArmList::CreateNode(MatchArmNode *node) {
    auto *tmp = new MatchArmList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = MatchArmList::GLOBAL_ID++;
    return tmp;
}

