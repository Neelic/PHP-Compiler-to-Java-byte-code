#include "CaseDefaultType.cpp"
#include <vector>
#include <string>

class ExprNode;
class StmtNode;
class StmtList;

class CaseDefaultStmtNode
{
public:
    ExprNode* expr;
    StmtList* stmtList;
    CaseDefaultType type;
    int cur_id;
    static int GLOBAL_ID;

    static CaseDefaultStmtNode* CreateFromCaseStmt(ExprNode* expr, StmtList* stmtList);
    static CaseDefaultStmtNode* CreateFromDefaultStmt(StmtList* stmtList);
    static CaseDefaultStmtNode* CreateFromFinallyStmt(StmtList* stmtList);
    std::string IdTag();
};