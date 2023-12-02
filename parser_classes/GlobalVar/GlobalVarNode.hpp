#include <vector>
#include <string>

class GetValueNode;

class GlobalVarNode
{
public:
    std::string* id;
    GetValueNode* get_value;

    static GlobalVarNode* CreateFromGlobalValue(GetValueNode* get_value, std::string* id);
};