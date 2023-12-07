#include "ExprList.hpp"

int ExprList::GLOBAL_ID = 0;

ExprList* ExprList::Create(std::vector<ExprNode*>* vector)
{
  ExprList* tmp = new ExprList();
  tmp->cur_id = ExprList::GLOBAL_ID++;
  return tmp;
}

void ExprList::Insert(ExprNode* element)
{
  this->vector->push_back(element);
}

