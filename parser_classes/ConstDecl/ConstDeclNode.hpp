
#ifndef PHP_COMPILER_CONST_DECL_NODE
#define PHP_COMPILER_CONST_DECL_NODE

#include <string>

class ExprNode;

class ConstDeclNode
{
public:
    std::string* id;
    ExprNode* expr;
    int cur_id;
    static int GLOBAL_ID;

    static ConstDeclNode* CreateFromConstDeclaration(std::string* id, ExprNode* expr);

    std::string* idTag() const;
};

#endif
