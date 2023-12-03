#include "FunctionDefType.cpp"

class FunctionDefNode
{
public:
    std::string* func_id;
    std::string* type_id;
    std::vector<ExprFuncNode*>* expr_func_list;
    FunctionDefType type;

    static FunctionDefNode* CreateFromDefWithNoType(std::string* func_id, std::vector<ExprFuncNode*>* expr_func_list);
    static FunctionDefNode* CreateFromDefWithType(std::string* func_id, std::vector<ExprFuncNode*>* expr_func_list, std::string* type_id);
};