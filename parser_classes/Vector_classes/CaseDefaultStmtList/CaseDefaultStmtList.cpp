#include "CaseDefaultStmtList.hpp"

int CaseDefaultStmtList::GLOBAL_ID = 0;

CaseDefaultStmtList* CaseDefaultStmtList::CreateNode(std::vector<CaseDefaultStmtNode *> *vector)
{
  CaseDefaultStmtList* tmp = new CaseDefaultStmtList();
  tmp->cur_id = CaseDefaultStmtList::GLOBAL_ID++;
  return tmp;
}

void CaseDefaultStmtList::Insert(CaseDefaultStmtNode* element)
{
  this->vector->push_back(element);
}