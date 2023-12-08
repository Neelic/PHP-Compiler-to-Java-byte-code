#include "TopStmtList.hpp"

int TopStmtList::GLOBAL_ID = 0;

TopStmtList* TopStmtList::CreateNode(std::vector<TopStmtNode*>* vector)
{
    TopStmtList* tmp = new TopStmtList();
    tmp->cur_id = TopStmtList::GLOBAL_ID++;
    return tmp;
}

void TopStmtList::Insert(TopStmtNode* element)
{
    this->vector->push_back(element);
}