#include "ClassExprType.cpp"

class ClassExprNode
{
public:
    std::vector<ClassAccessMod>* access_mod_list;
    GetValueNode* get_value;
    std::string* id;
    ExprNode* expr;
    std::vector<ConstDeclNode*>* const_decl_list;
    ClassExprType type;

    static ClassExprNode* CreateFromGetValueAssign(std::vector<ClassAccessMod>* access_mod_list, GetValueNode* get_value, std::string* id, ExprNode* expr);
    static ClassExprNode* CreateFromGetValue(std::vector<ClassAccessMod>* access_mod_list, GetValueNode* get_value, std::string* id);
    static ClassExprNode* CreateFromConstant(std::vector<ClassAccessMod>* access_mod_list, std::vector<ConstDeclNode*>* const_decl_list);
};