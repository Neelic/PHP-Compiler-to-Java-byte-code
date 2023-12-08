#include "MatchArmList.hpp"

int MatchArmList::GLOBAL_ID = 0;

MatchArmList* MatchArmList::CreateNode(std::vector<MatchArmNode*>* vector)
{
  MatchArmList* tmp = new MatchArmList();
  tmp->cur_id = MatchArmList::GLOBAL_ID++;
  return tmp;
}

void MatchArmList::Insert(MatchArmNode* element)
{
  this->vector->push_back(element);
}