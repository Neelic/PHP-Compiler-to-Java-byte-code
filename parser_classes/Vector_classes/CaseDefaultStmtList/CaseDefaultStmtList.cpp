#include "CaseDefaultStmtList.hpp"

int CaseDefaultStmtList::GLOBAL_ID = 0;

CaseDefaultStmtList *CaseDefaultStmtList::CreateNode(CaseDefaultStmtNode *node) {
    auto *tmp = new CaseDefaultStmtList();
    if (node != nullptr)
        tmp->vector.push_back(node);

    tmp->cur_id = CaseDefaultStmtList::GLOBAL_ID++;
    return tmp;
}

std::string CaseDefaultStmtList::IdTag() const {
    return std::string("CaseDefaultStmtList") + std::to_string(this->cur_id);
}

