#include "ForEachStmtType.cpp"
#include <vector>
#include <string>

class ExprNode;
class StmtNode;
class StmtList;

class ForEachStmtNode
{
public:
    ExprNode* expr_left;
    ExprNode* expr_right;
    StmtNode* stmt;
    std::string* id;
    StmtList* stmtList;
    ForEachStmtType type;

    static ForEachStmtNode* CreateFromForeachStmt(ExprNode* expr_left, ExprNode* expr_right, StmtNode* stmt);
    static ForEachStmtNode* CreateFromForeachRightArrowStmt(ExprNode* expr_left, ExprNode* expr_right, std::string* id, StmtNode* stmt);
    static ForEachStmtNode* CreateFromForeachRightArrowPointerStmt(ExprNode* expr_left, ExprNode* expr_right, std::string* id, StmtNode* stmt);
    static ForEachStmtNode* CreateFromEndForeachStmt(ExprNode* expr_left, ExprNode* expr_right, StmtList* stmtList);
    static ForEachStmtNode* CreateFromEndForeachRightArrowStmt(ExprNode* expr_left, ExprNode* expr_right, std::string* id, StmtList* stmtList);
    static ForEachStmtNode* CreateFromEndForeachRightArrowPointerStmt(ExprNode* expr_left, ExprNode* expr_right, std::string* id, StmtList* stmtList);
};