#include <string>

class ExprNode;

class ConstDeclNode
{
public:
    std::string* id;
    ExprNode* expr;

    static ConstDeclNode* CreateFromConstDeclaration(std::string* id, ExprNode* expr);
};