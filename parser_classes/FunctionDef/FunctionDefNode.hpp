#include <string>
#include "FunctionDefType.cpp"

class ExprFuncList;

class FunctionDefNode
{
public:
    std::string* func_id;
    std::string* type_id;
    ExprFuncList* expr_func_list;
    FunctionDefType type;
    int cur_id;
    static int GLOBAL_ID;

    static FunctionDefNode* CreateFromDefWithNoType(std::string* func_id, ExprFuncList* expr_func_list);
    static FunctionDefNode* CreateFromDefWithType(std::string* func_id, ExprFuncList* expr_func_list, std::string* type_id);

    std::string* idTag() const;
};