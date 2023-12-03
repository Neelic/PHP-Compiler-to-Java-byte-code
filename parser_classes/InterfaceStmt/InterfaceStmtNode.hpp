class InterfaceStmtNode
{
public:
    std::vector<ClassAccessMod>* access_mod;
    FunctionDefNode* function_def;

    static InterfaceStmtNode* Create(std::vector<ClassAccessMod>* access_mod, FunctionDefNode* function_def);
};
