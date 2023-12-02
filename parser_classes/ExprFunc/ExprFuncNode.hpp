#include "ExprFuncType.cpp"

class ExprFuncNode
{
public:
    GetValueFuncNode* get_value_func;
    ExprNode* expr;
    ExprFuncType type;

    static ExprFuncNode* CreateFromGetValueFunc(GetValueFuncNode* get_value_func);
    static ExprFuncNode* CreateFromGetValueFuncAssign(GetValueFuncNode* get_value_func, ExprNode* expr);
};