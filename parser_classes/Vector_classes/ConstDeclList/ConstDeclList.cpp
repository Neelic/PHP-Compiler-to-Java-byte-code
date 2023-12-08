#include "ConstDeclList.hpp"

int ConstDeclList::GLOBAL_ID = 0;

ConstDeclList* ConstDeclList::Create(std::vector<ConstDeclNode*>* vector)
{
  ConstDeclList* tmp = new ConstDeclList();
  tmp->cur_id = ConstDeclList::GLOBAL_ID++;
  return tmp;
}

void ConstDeclList::Insert(ConstDeclNode* element)
{
  this->vector->push_back(element);
}