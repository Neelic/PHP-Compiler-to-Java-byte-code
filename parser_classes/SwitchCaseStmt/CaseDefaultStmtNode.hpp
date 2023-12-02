#include "CaseDefaultType.cpp"

class ExprNode;

class CaseDefaultStmtNode
{
public:
    ExprNode* expr;
    std::vector<StmtNode*>* stmtList;
    CaseDefaultType type;

    static CaseDefaultStmtNode* CreateFromCaseStmt(ExprNode* expr, std::vector<StmtNode*>* stmtList);
    static CaseDefaultStmtNode* CreateFromDefaultStmt(std::vector<StmtNode*>* stmtList);
    static CaseDefaultStmtNode* CreateFromFinallyStmt(std::vector<StmtNode*>* stmtList);
};