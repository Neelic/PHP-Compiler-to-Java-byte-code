#include "IfStmtType.cpp"

class IfStmtNode
{
public:
    IfStmtType type;
    ExprNode* expr;
    StmtNode* stmt_main;
    StmtNode* stmt_else;
    std::vector<StmtNode*>* stmtList;

    static IfStmtNode* CreateFromIfStmt(ExprNode* expr, StmtNode* stmt_main);
    static IfStmtNode* CreateFromIfElseStmt(ExprNode* expr, StmtNode* stmt_main, StmtNode* stmt_else);
    static IfStmtNode* CreateFromIfEndIfStmt(ExprNode* expr, std::vector<StmtNode*>* stmtList);
    static IfStmtNode* CreateFromIfElseEndIfStmt(ExprNode* expr, StmtNode* stmt_main, StmtNode* stmt_else, std::vector<StmtNode*>* stmtList);
};