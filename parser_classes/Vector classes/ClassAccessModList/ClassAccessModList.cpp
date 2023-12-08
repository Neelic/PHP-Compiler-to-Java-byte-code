#include "ClassAccessModList.hpp"

int ClassAccessModList::GLOBAL_ID = 0;

ClassAccessModList* ClassAccessModList::Create(std::vector<ClassAccessMod*>* vector)
{
  ClassAccessModList* tmp = new ClassAccessModList();
  tmp->cur_id = ClassAccessModList::GLOBAL_ID++;
  return tmp;
}

void ClassAccessModList::Insert(ClassAccessMod* element)
{
  this->vector->push_back(element);
}