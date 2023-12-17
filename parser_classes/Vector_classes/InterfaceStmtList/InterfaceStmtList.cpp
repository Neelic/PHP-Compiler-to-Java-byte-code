#include "InterfaceStmtList.hpp"

int InterfaceStmtList::GLOBAL_ID = 0;

InterfaceStmtList *InterfaceStmtList::CreateNode(InterfaceStmtNode *node) {
    auto *tmp = new InterfaceStmtList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = InterfaceStmtList::GLOBAL_ID++;
    return tmp;
}

std::string *InterfaceStmtList::idTag() const {
    auto* tmp = new std::string(std::string("InterfaceStmtList") + std::to_string(this->cur_id));
    return tmp;
}