#include <string>

class GetValueNode
{
public:
    int count = 1;
    int cur_id;
    static int GLOBAL_ID;

    static GetValueNode* CreateNode();

    std::string IdTag();
};