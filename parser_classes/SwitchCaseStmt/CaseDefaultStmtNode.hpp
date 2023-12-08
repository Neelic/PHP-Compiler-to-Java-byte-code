#include "CaseDefaultType.cpp"
#include <vector>

class ExprNode;
class StmtNode;
class StmtList;

class CaseDefaultStmtNode
{
public:
    ExprNode* expr;
    StmtList* stmtList;
    CaseDefaultType type;

    static CaseDefaultStmtNode* CreateFromCaseStmt(ExprNode* expr, StmtList* stmtList);
    static CaseDefaultStmtNode* CreateFromDefaultStmt(StmtList* stmtList);
    static CaseDefaultStmtNode* CreateFromFinallyStmt(StmtList* stmtList);
};