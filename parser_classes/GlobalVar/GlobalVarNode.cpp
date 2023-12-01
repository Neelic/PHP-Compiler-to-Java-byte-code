#include "GlobalVarNode.hpp"

GlobalVarNode* GlobalVarNode::CreateFromGlobalValue(GetValueNode* get_value, std::string* id)
{
    GlobalVarNode* tmp = new GlobalVarNode();
    tmp->get_value = get_value;
    tmp->id = id;
    return tmp;
}