#include <string>

class ClassAccessModList;
class FunctionDefNode;

class InterfaceStmtNode
{
public:
    ClassAccessModList* access_mod;
    FunctionDefNode* function_def;
    int cur_id;
    static int GLOBAL_ID;

    static InterfaceStmtNode* CreateNode(ClassAccessModList* access_mod, FunctionDefNode* function_def);

    std::string* idTag() const;
};
