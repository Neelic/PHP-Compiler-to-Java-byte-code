#include "IdListNode.hpp"

int IdListNode::GLOBAL_ID = 0;

IdListNode* IdListNode::CreateNode(std::vector<std::string*>* vector)
{
  IdListNode* tmp = new IdListNode();
  tmp->cur_id = IdListNode::GLOBAL_ID++;
  return tmp;
}

void IdListNode::Insert(std::string* element)
{
  this->vector->push_back(element);
}