#include <string>

#ifndef TOP_STMT_NODE_H
#define TOP_STMT_NODE_H
#include "TopStmtType.cpp"

extern std::string GRAPH_STR;

class StmtNode;
class FunctionStmtDeclNode;
class ClassStmtDeclNode;
class InterfaceStmtDeclNode;
class TraitStmtDeclNode;

class TopStmtNode
{
public:
    StmtNode* stmt;
    FunctionStmtDeclNode* func_stmt_decl;
    ClassStmtDeclNode* class_stmt_decl;
    InterfaceStmtDeclNode* interface_stmt_decl;
    TraitStmtDeclNode* trait_stmt_decl;
    TopStmtType type;
    int cur_id;
    static int GLOBAL_ID;

    static TopStmtNode* CreateFromStmt(StmtNode* stmt);
    static TopStmtNode* CreateFromFunctionDecl(FunctionStmtDeclNode* func_stmt_decl);
    static TopStmtNode* CreateFromClassDecl(ClassStmtDeclNode* class_stmt_decl);
    static TopStmtNode* CreateFromInterfaceDecl(InterfaceStmtDeclNode* interface_stmt_decl);
    static TopStmtNode* CreateFromTraitDecl(TraitStmtDeclNode* trait_stmt_decl);

    std::string IdTag();
};

#endif