#include <string>
#include "StaticVarType.cpp"

class ExprNode;

class StaticVarNode
{
public:
    std::string* id;
    ExprNode* expr;
    StaticVarType type;
    int cur_id;
    static int GLOBAL_ID;

    static StaticVarNode* CreateFromId(std::string* id);
    static StaticVarNode* CreateFromIdAssign(std::string* id, ExprNode* expr);

    std::string IdTag();
};