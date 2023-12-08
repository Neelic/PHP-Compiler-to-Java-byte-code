#include "WhileStmtType.cpp"

class ExprNode;
class StmtNode;
class StmtList;

class WhileStmtNode
{
public:
    ExprNode* expr;
    StmtNode* stmt;
    StmtList* stmtList;
    WhileStmtType type;

    static WhileStmtNode* CreateFromWhileStmt(ExprNode* expr, StmtNode* stmt);
    static WhileStmtNode* CreateFromEndWhileStmt(ExprNode* expr, StmtList* stmtList);
};