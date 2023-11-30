#include "ForStmtType.cpp"

class ForStmtNode
{
public:
    ExprNode* expr_left;
    ExprNode* expr_central;
    ExprNode* expr_right;
    StmtNode* stmt;
    std::vector<StmtNode*>* stmtList;
    ForStmtType type;

    static ForStmtNode* CreateFromForStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, StmtNode* stmt);
    static ForStmtNode* CreateFromForEndStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, std::vector<StmtNode*>* stmtList);
};