#ifndef PHP_COMPILER_EXPR_FUNC_NODE
#define PHP_COMPILER_EXPR_FUNC_NODE

#include <vector>
#include <string>

class ExprFuncNode;

class ExprFuncList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<ExprFuncNode *> vector;

    static ExprFuncList *CreateNode(ExprFuncNode *node);
    
    std::string* idTag() const;
};

#endif
