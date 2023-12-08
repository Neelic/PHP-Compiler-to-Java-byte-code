#include "StaticVarList.hpp"

int StaticVarList::GLOBAL_ID = 0;

StaticVarList* StaticVarList::CreateNode(std::vector<StaticVarNode*>* vector)
{
  StaticVarList* tmp = new StaticVarList();
  tmp->cur_id = StaticVarList::GLOBAL_ID++;
  return tmp;
}

void StaticVarList::Insert(StaticVarNode* element)
{
  this->vector->push_back(element);
}