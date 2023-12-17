#include "GetValueNode.hpp"

int GetValueNode::GLOBAL_ID = 0;

std::string *GetValueNode::idTag() const {
    auto* tmp = new std::string(std::string("GetValue") + std::to_string(this->cur_id));
    return tmp;
}

GetValueNode *GetValueNode::CreateNode()
{
    GetValueNode* tmp = new GetValueNode();
    tmp->count++;
    tmp->cur_id = GetValueNode::GLOBAL_ID++;
    return tmp;
}
