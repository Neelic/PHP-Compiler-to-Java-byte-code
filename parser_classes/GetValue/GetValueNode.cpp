#include "GetValueNode.hpp"

int GetValueNode::GLOBAL_ID = 0;

std::string GetValueNode::IdTag() {
    return std::string("GetValue") + std::to_string(this->cur_id);
}

GetValueNode *GetValueNode::CreateNode()
{
    GetValueNode* tmp = new GetValueNode();
    tmp->count++;
    tmp->cur_id = GetValueNode::GLOBAL_ID++;
    return tmp;
}
