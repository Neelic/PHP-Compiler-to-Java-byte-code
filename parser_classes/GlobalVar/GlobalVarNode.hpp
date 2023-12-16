#include <vector>
#include <string>

class GetValueNode;

class GlobalVarNode
{
public:
    std::string* id;
    GetValueNode* get_value;
    int cur_id;
    static int GLOBAL_ID;

    static GlobalVarNode* CreateFromGlobalValue(GetValueNode* get_value, std::string* id);

    std::string IdTag();
};