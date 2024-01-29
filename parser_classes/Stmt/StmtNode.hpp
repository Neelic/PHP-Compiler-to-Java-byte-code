#ifndef PHP_COMPILER_STMT_NODE
#define PHP_COMPILER_STMT_NODE

#include "../Stmt/StmtType.cpp"
#include "StmtList.hpp"
// #include "../Vector classes/ConstDeclList/ConstDeclList.hpp";
#include <vector>
#include <string>

class ExprNode;

class IfStmtNode;

class SwitchStmtNode;

class WhileStmtNode;

class DoWhileStmtNode;

class ForStmtNode;

class ForEachStmtNode;

class TryCatchStmtNode;

class GlobalVarNode;

class StaticVarNode;

class MatchStmtNode;

class ConstDeclNode;

class HtmlStmtNode;

class ConstDeclList;

class StaticVarList;

class GlobalVarList;

class StmtNode {
public:
    ExprNode *expr_left = nullptr;
    ExprNode *expr_right = nullptr;
    IfStmtNode *if_stmt;
    SwitchStmtNode *switch_stmt;
    StmtList *stmtList;
    StaticVarList *static_var;
    GlobalVarList *global_var;
    WhileStmtNode *while_stmt;
    DoWhileStmtNode *do_while_stmt;
    ForStmtNode *for_stmt;
    ForEachStmtNode *foreach_stmt;
    TryCatchStmtNode *try_catch_stmt;
    MatchStmtNode *match_stmt;
    ConstDeclList *const_decl;
    HtmlStmtNode *html_stmt;
    StmtType type;
    int cur_id;
    static int GLOBAL_ID;

    static StmtNode *CreateFromExpr(ExprNode *expr);

    static StmtNode *CreateFromIfStmt(IfStmtNode *if_stmt);

    static StmtNode *CreateFromSwitchStmt(SwitchStmtNode *switch_stmt);

    static StmtNode *CreateFromStmtList(StmtList *stmtList);

    static StmtNode *CreateFromStaticVar(StaticVarList *static_var);

    static StmtNode *CreateFromGlobalVar(GlobalVarList *global_var);

    static StmtNode *CreateFromWhileStmt(WhileStmtNode *while_stmt);

    static StmtNode *CreateFromDoWhileStmt(DoWhileStmtNode *do_while_stmt);

    static StmtNode *CreateFromForStmt(ForStmtNode *for_stmt);

    static StmtNode *CreateFromForEachStmt(ForEachStmtNode *foreach_stmt);

    static StmtNode *CreateFromThrowStmt(ExprNode *expr);

    static StmtNode *CreateFromTryCatchStmt(TryCatchStmtNode *try_catch_stmt);

    static StmtNode *CreateFromMatchStmt(MatchStmtNode *match_stmt);

    static StmtNode *CreateFromConstDecl(ConstDeclList *const_decl);

    static StmtNode *CreateFromReturnStmt(ExprNode *expr_left);

    static StmtNode *CreateFromYieldStmt(ExprNode *expr_left);

    static StmtNode *CreateFromYieldDoubleArrowStmt(ExprNode *expr_left, ExprNode *expr_right);

    static StmtNode *CreateFromHtmlStmt(HtmlStmtNode *html_stmt);

    static StmtNode *CreateFromBreakStmt();

    static StmtNode *CreateFromTEchoStmt(ExprNode *expr_left);

    static StmtNode *CreateFromContinueStmt();

    std::string *idTag() const;
};

#endif
