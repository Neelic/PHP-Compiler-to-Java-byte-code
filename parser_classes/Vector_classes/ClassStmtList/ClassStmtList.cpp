#include "ClassStmtList.hpp"

int ClassStmtList::GLOBAL_ID = 0;

ClassStmtList *ClassStmtList::CreateNode(ClassStmtNode *node) {
    auto *tmp = new ClassStmtList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = ClassStmtList::GLOBAL_ID++;
    return tmp;
}

std::string ClassStmtList::IdTag() const {
    return std::string("ClassStmtList") + std::to_string(this->cur_id);
}

