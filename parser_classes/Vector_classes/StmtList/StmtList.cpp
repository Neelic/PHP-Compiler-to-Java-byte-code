#include "StmtList.hpp"

int StmtList::GLOBAL_ID = 0;

StmtList* StmtList::CreateNode(std::vector<StmtNode*>* vector)
{
  StmtList* tmp = new StmtList();
  tmp->cur_id = StmtList::GLOBAL_ID++;
  return tmp;
}

void StmtList::Insert(StmtNode* element)
{
  this->vector->push_back(element);
}