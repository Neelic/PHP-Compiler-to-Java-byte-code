#include "TopStmtType.cpp"

class TopStmtNode
{
public:
    StmtNode* stmt;
    FunctionStmtDeclNode* func_stmt_decl;
    ClassStmtDeclNode* class_stmt_decl;
    InterfaceStmtDeclNode* interface_stmt_decl;
    TraitStmtDeclNode* trait_stmt_decl;
    TopStmtType type;

    static TopStmtNode* CreateFromStmt(StmtNode* stmt);
    static TopStmtNode* CreateFromFunctionDecl(FunctionStmtDeclNode* func_stmt_decl);
    static TopStmtNode* CreateFromClassDecl(ClassStmtDeclNode* class_stmt_decl);
    static TopStmtNode* CreateFromInterfaceDecl(InterfaceStmtDeclNode* interface_stmt_decl);
    static TopStmtNode* CreateFromTraitDecl(TraitStmtDeclNode* trait_stmt_decl);
};