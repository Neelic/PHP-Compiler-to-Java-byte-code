#include "ElseIfDotList.h"

int ElseIfDotList::GLOBAL_ID=0;

ElseIfDotList *ElseIfDotList::Create(IfStmtNode *node) {
    auto *tmp = new ElseIfDotList;
    tmp->cur_id = ElseIfDotList::GLOBAL_ID++;
    if (node != nullptr)
        tmp->vector.push_back(node);
    return tmp;
}
