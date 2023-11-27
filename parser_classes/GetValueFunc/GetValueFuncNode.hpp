#include "GetValueFuncType.cpp"

class GetValueFuncNode
{
public:
    GetValueFuncType type;
    std::string* id_value;
    std::string* id_type;


    static GetValueFuncNode* CreateFromRefValue(std::string* id_value);
    static GetValueFuncNode* CreateFromGetValue(std::string* id_value);
    static GetValueFuncNode* CreateFromRefValueWithType(std::string* id_value, std::string* id_type);
    static GetValueFuncNode* CreateFromGetValueWithType(std::string* id_value, std::string* id_type);
};