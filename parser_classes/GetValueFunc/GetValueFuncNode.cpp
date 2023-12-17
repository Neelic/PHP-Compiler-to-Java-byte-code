#include "GetValueFuncNode.hpp"

int GetValueFuncNode::GLOBAL_ID = 0;

std::string GetValueFuncNode::IdTag() {
    return std::string("GetValueFunc") + std::to_string(this->cur_id);
}

GetValueFuncNode* GetValueFuncNode::CreateFromRefValue(std::string* id_value)
{
    GetValueFuncNode* tmp = new GetValueFuncNode();
    tmp->id_value = id_value;
    tmp->type = GetValueFuncType::with_ref_no_type;
    tmp->cur_id = GetValueFuncNode::GLOBAL_ID++;
    return tmp;
}

GetValueFuncNode* GetValueFuncNode::CreateFromGetValue(std::string* id_value)
{
    GetValueFuncNode* tmp = new GetValueFuncNode();
    tmp->id_value = id_value;
    tmp->type = GetValueFuncType::no_ref_no_type;
    tmp->cur_id = GetValueFuncNode::GLOBAL_ID++;
    return tmp;
}

GetValueFuncNode* GetValueFuncNode::CreateFromRefValueWithType(std::string* id_value, std::string* id_type)
{
    GetValueFuncNode* tmp = new GetValueFuncNode();
    tmp->id_value = id_value;
    tmp->id_type = id_type;
    tmp->type = GetValueFuncType::with_ref_with_type;
    tmp->cur_id = GetValueFuncNode::GLOBAL_ID++;
    return tmp;
}

GetValueFuncNode *GetValueFuncNode::CreateFromGetValueWithType(std::string *id_value, std::string *id_type)
{
    GetValueFuncNode* tmp = new GetValueFuncNode();
    tmp->id_value = id_value;
    tmp->id_type = id_type;
    tmp->type = GetValueFuncType::no_ref_with_type;
    tmp->cur_id = GetValueFuncNode::GLOBAL_ID++;
    return tmp;
}
