#include "GetValueFuncNode.hpp"

GetValueFuncNode* GetValueFuncNode::CreateFromRefValue(std::string* id_value)
{
    GetValueFuncNode* tmp = new GetValueFuncNode();
    tmp->id_value = id_value;
    tmp->type = GetValueFuncType::with_ref_no_type;
    return tmp;
}

GetValueFuncNode* GetValueFuncNode::CreateFromGetValue(std::string* id_value)
{
    GetValueFuncNode* tmp = new GetValueFuncNode();
    tmp->id_value = id_value;
    tmp->type = GetValueFuncType::no_ref_no_type;
    return tmp;
}

GetValueFuncNode* GetValueFuncNode::CreateFromRefValueWithType(std::string* id_value, std::string* id_type)
{
    GetValueFuncNode* tmp = new GetValueFuncNode();
    tmp->id_value = id_value;
    tmp->id_type = id_type;
    tmp->type = GetValueFuncType::with_ref_with_type;
    return tmp;
}

GetValueFuncNode* GetValueFuncNode::CreateFromRefValueWithType(std::string* id_value, std::string* id_type)
{
    GetValueFuncNode* tmp = new GetValueFuncNode();
    tmp->id_value = id_value;
    tmp->id_type = id_type;
    tmp->type = GetValueFuncType::no_ref_with_type;
    return tmp;
}
