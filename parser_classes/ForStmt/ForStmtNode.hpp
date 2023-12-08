#include "ForStmtType.cpp"
#include <vector>

class ExprNode;
class StmtNode;
class StmtList;

class ForStmtNode
{
public:
    ExprNode* expr_left;
    ExprNode* expr_central;
    ExprNode* expr_right;
    StmtNode* stmt;
    StmtList* stmtList;
    ForStmtType type;

    static ForStmtNode* CreateFromForStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, StmtNode* stmt);
    static ForStmtNode* CreateFromForEndStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, StmtList* stmtList);
};