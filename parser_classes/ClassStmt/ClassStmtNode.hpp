#include "ClassStmtType.cpp"

class ClassStmtNode
{
public:
    ClassExprNode* class_expr;
    std::vector<ClassAccessMod>* access_mod;
    FunctionStmtDeclNode* function_stmt_decl;
    std::vector<std::string*>* id_list;
    ClassStmtDeclNode* class_stmt_decl;
    ClassStmtType type;

    static ClassStmtNode* CreateFromClassExpr(ClassExprNode* class_expr);
    static ClassStmtNode* CreateFromFunctionStmtDecl(std::vector<ClassAccessMod>* access_mod, FunctionStmtDeclNode* function_stmt_decl);
    static ClassStmtNode* CreateFromIdList(std::vector<std::string*>* id_list);
    static ClassStmtNode* CreateFromClassStmtDecl(ClassStmtDeclNode* class_stmt_decl);
};