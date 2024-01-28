#ifndef FUNCTION_DEF_NODE_H
#define FUNCTION_DEF_NODE_H

#include <string>
#include "FunctionDefType.cpp"
#include "ExprFuncList.hpp"

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

#endif
