#include "ClassStmtList.hpp"

int ClassStmtList::GLOBAL_ID = 0;

ClassStmtList* ClassStmtList::CreateNode(std::vector<ClassStmtNode*>* vector)
{
  ClassStmtList* tmp = new ClassStmtList();
  tmp->cur_id = ClassStmtList::GLOBAL_ID++;
  return tmp;
}

void ClassStmtList::Insert(ClassStmtNode* element)
{
  this->vector->push_back(element);
}