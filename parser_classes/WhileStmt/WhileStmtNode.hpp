#include "WhileStmtType.cpp"

class WhileStmtNode
{
public:
    ExprNode* expr;
    StmtNode* stmt;
    std::vector<StmtNode*>* stmtList;
    WhileStmtType type;

    static WhileStmtNode* CreateFromWhileStmt(ExprNode* expr, StmtNode* stmt);
    static WhileStmtNode* CreateFromEndWhileStmt(ExprNode* expr, std::vector<StmtNode*>* stmtList);
};