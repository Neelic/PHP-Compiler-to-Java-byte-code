#include "ClassExprNode.hpp"

int ClassExprNode::GLOBAL_ID = 0;

std::string *ClassExprNode::idTag() const {
    auto* tmp = new std::string(std::string("ClassExpr") + std::to_string(this->cur_id));
    return tmp;
}

ClassExprNode *
ClassExprNode::CreateFromGetValueAssign(ClassAccessModList *access_mod_list, GetValueNode *get_value, std::string *id,
                                        ExprNode *expr, std::string *id_type)
{
    ClassExprNode* tmp = new ClassExprNode();
    tmp->access_mod_list = access_mod_list;
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->expr = expr;
    tmp->id_type = id_type;
    tmp->type = ClassExprType::get_value_assign_class_type;
    tmp->cur_id = ClassExprNode::GLOBAL_ID++;
    return tmp;
}

ClassExprNode *
ClassExprNode::CreateFromGetValue(ClassAccessModList *access_mod_list, GetValueNode *get_value, std::string *id,
                                  std::string *id_type)
{
    ClassExprNode* tmp = new ClassExprNode();
    tmp->access_mod_list = access_mod_list;
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->id_type = id_type;
    tmp->type = ClassExprType::get_value_class_type;
    tmp->cur_id = ClassExprNode::GLOBAL_ID++;
    return tmp;
}

ClassExprNode* ClassExprNode::CreateFromConstant(ClassAccessModList* access_mod_list, ConstDeclList* const_decl_list)
{
    ClassExprNode* tmp = new ClassExprNode();
    tmp->access_mod_list = access_mod_list;
    tmp->const_decl_list = const_decl_list;
    tmp->type = ClassExprType::const_class_type;
    tmp->cur_id = ClassExprNode::GLOBAL_ID++;
    return tmp;
}