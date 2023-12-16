#include "GlobalVarNode.hpp"

int GlobalVarNode::GLOBAL_ID = 0;

std::string GlobalVarNode::IdTag() {
    return std::string("GlobalVar") + std::to_string(this->cur_id);
}

GlobalVarNode* GlobalVarNode::CreateFromGlobalValue(GetValueNode* get_value, std::string* id)
{
    GlobalVarNode* tmp = new GlobalVarNode();
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->cur_id = GlobalVarNode::GLOBAL_ID++;
    return tmp;
}