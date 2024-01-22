#include <iostream>
#include "ClassStmtNode.hpp"

int ClassStmtNode::GLOBAL_ID = 0;

std::string *ClassStmtNode::idTag() const {
    auto* tmp = new std::string(std::string("ClassStmt") + std::to_string(this->cur_id));
    return tmp;
}

ClassStmtNode* ClassStmtNode::CreateFromClassExpr(ClassExprNode* class_expr)
{
    ClassStmtNode* tmp = new ClassStmtNode();
    tmp->class_expr = class_expr;
    tmp->type = ClassStmtType::class_expr_stmt_type;
    tmp->cur_id = ClassStmtNode::GLOBAL_ID++;
    return tmp;
}

ClassStmtNode* ClassStmtNode::CreateFromFunctionStmtDecl(ClassAccessModList* access_mod, FunctionStmtDeclNode* function_stmt_decl)
{
    ClassStmtNode* tmp = new ClassStmtNode();
    tmp->access_mod = access_mod;
    tmp->function_stmt_decl = function_stmt_decl;
    tmp->type = ClassStmtType::function_decl_type;
    tmp->cur_id = ClassStmtNode::GLOBAL_ID++;
    return tmp;
}

static ClassStmtNode* CreateFromFunctionDef(ClassAccessModList* access_mod, FunctionDefNode* function_def)
{
    ClassStmtNode* tmp = new ClassStmtNode();
    tmp->access_mod = access_mod;
    tmp->function_def = function_def;
    tmp->type = ClassStmtType::function_def;
    tmp->cur_id = ClassStmtNode::GLOBAL_ID++;
    return tmp;
}

ClassStmtNode* ClassStmtNode::CreateFromIdList(IdListNode* id_list)
{
    ClassStmtNode* tmp = new ClassStmtNode();
    tmp->id_list = id_list;
    tmp->type = ClassStmtType::id_list_type;
    tmp->cur_id = ClassStmtNode::GLOBAL_ID++;
    return tmp;
}

ClassStmtNode* ClassStmtNode::CreateFromClassStmtDecl(ClassStmtDeclNode* class_stmt_decl)
{
    ClassStmtNode* tmp = new ClassStmtNode();
    tmp->class_stmt_decl = class_stmt_decl;
    tmp->type = ClassStmtType::class_stmt_decl_type;
    tmp->cur_id = ClassStmtNode::GLOBAL_ID++;
    return tmp;
}

ClassStmtNode *ClassStmtNode::CreateFromFunctionDef(ClassAccessModList *access_mod, FunctionDefNode *function_def) {
    auto *tmp = new ClassStmtNode();
    tmp->access_mod = access_mod;
    tmp->function_def = function_def;
    tmp->type = ClassStmtType::function_def;
    tmp->cur_id = ClassStmtNode::GLOBAL_ID++;
    return tmp;
}
