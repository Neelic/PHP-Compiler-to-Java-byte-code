#include "ClassAccessModList.hpp"

int ClassAccessModList::GLOBAL_ID = 0;

ClassAccessModList* ClassAccessModList::CreateNode(std::vector<ClassAccessModNode*>* vector)
{
  ClassAccessModList* tmp = new ClassAccessModList();
  tmp->cur_id = ClassAccessModList::GLOBAL_ID++;
  return tmp;
}

void ClassAccessModList::Insert(ClassAccessModNode* element)
{
  this->vector->push_back(element);
}