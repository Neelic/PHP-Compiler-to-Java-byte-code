#include "TopStmtNode.hpp"

TopStmtNode* TopStmtNode::CreateFromStmt(StmtNode* stmt)
{
    TopStmtNode* tmp = new TopStmtNode();
    tmp->stmt = stmt;
    tmp->type = TopStmtType::stmt_top_type;
    return tmp;
}

TopStmtNode* TopStmtNode::CreateFromFunctionDecl(FunctionStmtDeclNode* func_stmt_decl)
{
    TopStmtNode* tmp = new TopStmtNode();
    tmp->func_stmt_decl = func_stmt_decl;
    tmp->type = TopStmtType::function_top_type;
    return tmp;
}

TopStmtNode* TopStmtNode::CreateFromClassDecl(ClassStmtDeclNode* class_stmt_decl)
{
    TopStmtNode* tmp = new TopStmtNode();
    tmp->class_stmt_decl = class_stmt_decl;
    tmp->type = TopStmtType::class_top_type;
    return tmp;
}

TopStmtNode* TopStmtNode::CreateFromInterfaceDecl(InterfaceStmtDeclNode* interface_stmt_decl)
{
    TopStmtNode* tmp = new TopStmtNode();
    tmp->interface_stmt_decl = interface_stmt_decl;
    tmp->type = TopStmtType::interface_top_type;
    return tmp;
}

TopStmtNode* TopStmtNode::CreateFromTraitDecl(TraitStmtDeclNode* trait_stmt_decl)
{
    TopStmtNode* tmp = new TopStmtNode();
    tmp->trait_stmt_decl = trait_stmt_decl;
    tmp->type = TopStmtType::trait_top_type;
    return tmp;
}
