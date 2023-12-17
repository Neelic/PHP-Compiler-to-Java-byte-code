#include "IfStmtType.cpp"
#include <vector>
#include <string>

class ExprNode;
class StmtNode;
class StmtList;

class IfStmtNode
{
public:
    IfStmtType type;
    ExprNode* expr;
    StmtNode* stmt_main;
    StmtNode* stmt_else;
    StmtList* stmtListMain;
    StmtList* stmtListElse;
    int cur_id;
    static int GLOBAL_ID;

    static IfStmtNode* CreateFromIfStmt(ExprNode* expr, StmtNode* stmt_main);
    static IfStmtNode* CreateFromIfElseStmt(ExprNode* expr, StmtNode* stmt_main, StmtNode* stmt_else);
    static IfStmtNode* CreateFromIfEndIfStmt(ExprNode* expr, StmtList* stmtListMain);
    static IfStmtNode* CreateFromIfElseEndIfStmt(ExprNode* expr, StmtList* stmtListMain, StmtList* stmtListElse);

    std::string IdTag();
};