#include "InterfaceStmtList.hpp"

int InterfaceStmtList::GLOBAL_ID = 0;

InterfaceStmtList* InterfaceStmtList::Create(std::vector<InterfaceStmtNode*>* vector)
{
  InterfaceStmtList* tmp = new InterfaceStmtList();
  tmp->cur_id = InterfaceStmtList::GLOBAL_ID++;
  return tmp;
}

void InterfaceStmtList::Insert(InterfaceStmtNode* element)
{
  this->vector->push_back(element);
}