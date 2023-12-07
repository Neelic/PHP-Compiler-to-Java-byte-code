class InterfaceStmtNode
{
public:
    ClassAccessModList* access_mod;
    FunctionDefNode* function_def;

    static InterfaceStmtNode* Create(ClassAccessModList* access_mod, FunctionDefNode* function_def);
};
