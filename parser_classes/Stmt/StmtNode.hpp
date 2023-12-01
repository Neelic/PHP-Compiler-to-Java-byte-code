#include "../Stmt/StmtType.cpp"

class StmtNode
{
public:
    ExprNode* expr_left;
    ExprNode* expr_right;
    IfStmtNode* if_stmt;
    SwitchStmtNode* switch_stmt;
    std::vector<StmtNode*>* stmtList;
    StaticVarNode* static_var;
    GlobalVarNode* global_var;
    WhileStmtNode* while_stmt;
    DoWhileStmtNode* do_while_stmt;
    ForStmtNode* for_stmt;
    ForEachStmtNode* foreach_stmt;
    TryCatchStmtNode* try_catch_stmt;
    MatchStmtNode* match_stmt;
    ConstDeclNode* const_decl;
    HtmlStmtNode* html_stmt;
    StmtType type;

    static StmtNode* CreateFromExpr(ExprNode* expr);
    static StmtNode* CreateFromIfStmt(IfStmtNode* if_stmt);
    static StmtNode* CreateFromSwitchStmt(SwitchStmtNode* switch_stmt);
    static StmtNode* CreateFromStmtList(std::vector<StmtNode*>* stmtList);
    static StmtNode* CreateFromStaticVar(StaticVarNode* static_var);
    static StmtNode* CreateFromGlobalVar(GlobalVarNode* global_var);
    static StmtNode* CreateFromWhileStmt(WhileStmtNode* while_stmt);
    static StmtNode* CreateFromDoWhileStmt(DoWhileStmtNode* do_while_stmt);
    static StmtNode* CreateFromForStmt(ForStmtNode* for_stmt);
    static StmtNode* CreateFromForEachStmt(ForEachStmtNode* foreach_stmt);
    static StmtNode* CreateFromThrowStmt(ExprNode* expr);
    static StmtNode* CreateFromTryCatchStmt(TryCatchStmtNode* try_catch_stmt);
    static StmtNode* CreateFromMatchStmt(MatchStmtNode* match_stmt);
    static StmtNode* CreateFromConstDecl(ConstDeclNode* const_decl);
    static StmtNode* CreateFromReturnStmt(ExprNode* expr_left);
    static StmtNode* CreateFromYieldStmt(ExprNode* expr_left);
    static StmtNode* CreateFromYieldDoubleArrowStmt(ExprNode* expr_left, ExprNode* expr_right);
    static StmtNode* CreateFromHtmlStmt(HtmlStmtNode* html_stmt);
    static StmtNode* CreateFromBreakStmt();
};