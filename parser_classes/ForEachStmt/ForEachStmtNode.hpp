#include "ForEachStmtType.cpp"

class ForEachStmtNode
{
public:
    ExprNode* expr_left;
    ExprNode* expr_right;
    StmtList* stmt;
    std::string id;
    std::vector<StmtList*>* stmtList;
    ForEachStmtType type;

    static ForEachStmtNode* CreateFromForeachStmt(ExprNode* expr_left, ExprNode* expr_right, StmtList* stmt);
    static ForEachStmtNode* CreateFromForeachRightArrowStmt(ExprNode* expr_left, ExprNode* expr_right, std::string id, StmtList* stmt);
    static ForEachStmtNode* CreateFromForeachRightArrowPointerStmt(ExprNode* expr_left, ExprNode* expr_right, std::string id, StmtList* stmt);
    static ForEachStmtNode* CreateFromEndForeachStmt(ExprNode* expr_left, ExprNode* expr_right, std::vector<StmtList*>* stmtList);
    static ForEachStmtNode* CreateFromEndForeachRightArrowStmt(ExprNode* expr_left, ExprNode* expr_right, std::string id, std::vector<StmtList*>* stmtList);
    static ForEachStmtNode* CreateFromEndForeachRightArrowPointerStmt(ExprNode* expr_left, ExprNode* expr_right, std::string id, std::vector<StmtList*>* stmtList);
};