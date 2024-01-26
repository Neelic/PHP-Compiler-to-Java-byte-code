#ifndef PHP_COMPILER_CLASS_EXPR_NODE
#define PHP_COMPILER_CLASS_EXPR_NODE

#include "ClassExprType.cpp"
#include <string>

class ClassAccessModList;

class GetValueNode;

class ExprNode;

class ConstDeclList;

class ClassExprNode {
public:
    ClassAccessModList *access_mod_list;
    GetValueNode *get_value;
    std::string *id;
    std::string *id_type;
    ExprNode *expr;
    ConstDeclList *const_decl_list;
    ClassExprType type;
    int cur_id;
    static int GLOBAL_ID;

    static ClassExprNode *
    CreateFromGetValueAssign(ClassAccessModList *access_mod_list, GetValueNode *get_value, std::string *id,
                             ExprNode *expr, std::string *id_type = nullptr);

    static ClassExprNode *
    CreateFromGetValue(ClassAccessModList *access_mod_list, GetValueNode *get_value, std::string *id,
                       std::string *id_type = nullptr);

    static ClassExprNode *CreateFromConstant(ClassAccessModList *access_mod_list, ConstDeclList *const_decl_list);

    std::string *idTag() const;
};

#endif
