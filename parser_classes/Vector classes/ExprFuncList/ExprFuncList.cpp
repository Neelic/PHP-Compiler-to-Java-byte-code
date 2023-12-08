#include "ExprFuncList.hpp"

int ExprFuncList::GLOBAL_ID = 0;

ExprFuncList* ExprFuncList::Create(std::vector<ExprFuncNode*>* vector)
{
  ExprFuncList* tmp = new ExprFuncList();
  tmp->cur_id = ExprFuncList::GLOBAL_ID++;
  return tmp;
}

void ExprFuncList::Insert(ExprFuncNode* element)
{
  this->vector->push_back(element);
}