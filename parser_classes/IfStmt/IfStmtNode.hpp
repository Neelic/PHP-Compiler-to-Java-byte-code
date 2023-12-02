#include "IfStmtType.cpp"

class ExprNode;
class StmtNode;

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
    static IfStmtNode* CreateFromIfElseEndIfStmt(ExprNode* expr, std::vector<StmtNode*>* stmt_main_list, std::vector<StmtNode*>* stmt_else_list); //TODO переделать
};