#include "IfStmtType.cpp"
#include <vector>

class ExprNode;
class StmtNode;

class IfStmtNode
{
public:
    IfStmtType type;
    ExprNode* expr;
    StmtNode* stmt_main;
    StmtNode* stmt_else;
    std::vector<StmtNode*>* stmtListMain;
    std::vector<StmtNode*>* stmtListElse;

    static IfStmtNode* CreateFromIfStmt(ExprNode* expr, StmtNode* stmt_main);
    static IfStmtNode* CreateFromIfElseStmt(ExprNode* expr, StmtNode* stmt_main, StmtNode* stmt_else);
    static IfStmtNode* CreateFromIfEndIfStmt(ExprNode* expr, std::vector<StmtNode*>* stmtListMain);
    static IfStmtNode* CreateFromIfElseEndIfStmt(ExprNode* expr, std::vector<StmtNode*>* stmtListMain, std::vector<StmtNode*>* stmtListElse);
};