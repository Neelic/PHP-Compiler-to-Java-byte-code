class ClassAccessModList;
class FunctionDefNode;

class InterfaceStmtNode
{
public:
    ClassAccessModList* access_mod;
    FunctionDefNode* function_def;

    static InterfaceStmtNode* CreateNode(ClassAccessModList* access_mod, FunctionDefNode* function_def);
};
