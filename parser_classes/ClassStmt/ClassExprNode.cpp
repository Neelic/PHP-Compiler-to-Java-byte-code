#include "ClassExprNode.hpp"

ClassExprNode* ClassExprNode::CreateFromGetValueAssign(std::vector<ClassAccessMod>* access_mod_list, GetValueNode* get_value, std::string* id, ExprNode* expr)
{
    ClassExprNode* tmp = new ClassExprNode();
    tmp->access_mod_list = access_mod_list;
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->expr = expr;
    tmp->type = ClassExprType::get_value_assign_type;
    return tmp;
}

ClassExprNode* ClassExprNode::CreateFromGetValue(std::vector<ClassAccessMod>* access_mod_list, GetValueNode* get_value, std::string* id)
{
    ClassExprNode* tmp = new ClassExprNode();
    tmp->access_mod_list = access_mod_list;
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->type = ClassExprType::get_value_type;
    return tmp;
}

ClassExprNode* ClassExprNode::CreateFromConstant(std::vector<ClassAccessMod>* access_mod_list, std::vector<ConstDeclNode*>* const_decl_list)
{
    ClassExprNode* tmp = new ClassExprNode();
    tmp->access_mod_list = access_mod_list;
    tmp->const_decl_list = const_decl_list;
    tmp->type = ClassExprType::const_type;
    return tmp;
}