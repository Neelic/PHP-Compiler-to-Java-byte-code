#include "GlobalVarNode.hpp"

int GlobalVarNode::GLOBAL_ID = 0;

std::string *GlobalVarNode::idTag() const {
    auto* tmp = new std::string(std::string("GlobalVar") + std::to_string(this->cur_id));
    return tmp;
}

GlobalVarNode* GlobalVarNode::CreateFromGlobalValue(GetValueNode* get_value, std::string* id)
{
    GlobalVarNode* tmp = new GlobalVarNode();
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->cur_id = GlobalVarNode::GLOBAL_ID++;
    return tmp;
}