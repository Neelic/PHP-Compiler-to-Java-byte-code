#include "ForStmtType.cpp"
#include <string>
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
    int cur_id;
    static int GLOBAL_ID;

    static ForStmtNode* CreateFromForStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, StmtNode* stmt);
    static ForStmtNode* CreateFromForEndStmt(ExprNode* expr_left, ExprNode* expr_central, ExprNode* expr_right, StmtList* stmtList);

    std::string* idTag() const;
};