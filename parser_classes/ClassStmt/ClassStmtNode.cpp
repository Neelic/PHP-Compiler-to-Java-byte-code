#include "ClassStmtNode.hpp"

ClassStmtNode* ClassStmtNode::CreateFromClassExpr(ClassExprNode* class_expr)
{
    ClassStmtNode* tmp = new ClassStmtNode();
    tmp->class_expr = class_expr;
    tmp->type = ClassStmtType::class_expr_stmt_type;
    return tmp;
}

ClassStmtNode* ClassStmtNode::CreateFromFunctionStmtDecl(std::vector<ClassAccessMod>* access_mod, FunctionStmtDeclNode* function_stmt_decl)
{
    ClassStmtNode* tmp = new ClassStmtNode();
    tmp->access_mod = access_mod;
    tmp->function_stmt_decl = function_stmt_decl;
    tmp->type = ClassStmtType::function_decl_type;
    return tmp;
}

ClassStmtNode* ClassStmtNode::CreateFromIdList(std::vector<std::string*>* id_list)
{
    ClassStmtNode* tmp = new ClassStmtNode();
    tmp->id_list = id_list;
    tmp->type = ClassStmtType::id_list_type;
    return tmp;
}

ClassStmtNode* ClassStmtNode::CreateFromClassStmtDecl(ClassStmtDeclNode* class_stmt_decl)
{
    ClassStmtNode* tmp = new ClassStmtNode();
    tmp->class_stmt_decl = class_stmt_decl;
    tmp->type = ClassStmtType::class_stmt_decl_type;
    return tmp;
}