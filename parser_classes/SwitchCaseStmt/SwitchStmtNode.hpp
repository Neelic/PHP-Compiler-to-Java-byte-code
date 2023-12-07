#include "SwitchStmtType.cpp"
#include <vector>

class ExprNode;
class CaseDefaultStmtNode;
class CaseDefaultStmtList;

class SwitchStmtNode
{
public:
    ExprNode* expr;
    CaseDefaultStmtList* defaultStmtList;
    SwitchStmtType type;

    static SwitchStmtNode* CreateFromSwitchStmt(ExprNode* expr);
    static SwitchStmtNode* CreateFromSwitchDefaultStmt(ExprNode* expr, CaseDefaultStmtList* defaultStmtList);
    static SwitchStmtNode* CreateFromSwitchDefaultEndswitchStmt(ExprNode* expr, CaseDefaultStmtList* defaultStmtList);
};