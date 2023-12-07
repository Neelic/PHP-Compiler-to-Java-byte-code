#include "GlobalVarList.hpp"

int GlobalVarList::GLOBAL_ID = 0;

GlobalVarList* GlobalVarList::Create(std::vector<GlobalVarNode*>* vector)
{
  GlobalVarList* tmp = new GlobalVarList();
  tmp->cur_id = GlobalVarList::GLOBAL_ID++;
  return tmp;
}

void GlobalVarList::Insert(GlobalVarNode* element)
{
  this->vector->push_back(element);
}