#include "TopStmtList.hpp"

int TopStmtList::GLOBAL_ID = 0;

TopStmtList *TopStmtList::CreateNode(TopStmtNode *node) {
    auto *tmp = new TopStmtList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = TopStmtList::GLOBAL_ID++;
    return tmp;
}

std::string* TopStmtList::idTag() const {
    auto* tmp = new std::string(std::string("TopStmtList") + std::to_string(this->cur_id));
    return tmp;
}
