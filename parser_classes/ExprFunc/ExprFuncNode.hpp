#include "ExprFuncType.cpp"
#include <string>

class GetValueFuncNode;
class ExprNode;

class ExprFuncNode
{
public:
    GetValueFuncNode* get_value_func;
    ExprNode* expr;
    ExprFuncType type;
    int cur_id;
    static int GLOBAL_ID;

    static ExprFuncNode* CreateFromGetValueFunc(GetValueFuncNode* get_value_func);
    static ExprFuncNode* CreateFromGetValueFuncAssign(GetValueFuncNode* get_value_func, ExprNode* expr);

    std::string* idTag() const;
};