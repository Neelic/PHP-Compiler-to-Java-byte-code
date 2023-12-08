#include "GetValueFuncList.hpp"

int GetValueFuncList::GLOBAL_ID = 0;

GetValueFuncList* GetValueFuncList::CreateNode(std::vector<GetValueFuncNode*>* vector)
{
  GetValueFuncList* tmp = new GetValueFuncList();
  tmp->cur_id = GetValueFuncList::GLOBAL_ID++;
  return tmp;
}

void GetValueFuncList::Insert(GetValueFuncNode* element)
{
  this->vector->push_back(element);
}