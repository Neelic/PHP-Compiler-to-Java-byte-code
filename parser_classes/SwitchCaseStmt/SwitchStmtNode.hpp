#include "SwitchStmtType.cpp"
#include <vector>
#include <string>

class ExprNode;
class CaseDefaultStmtNode;
class CaseDefaultStmtList;

class SwitchStmtNode
{
public:
    ExprNode* expr;
    CaseDefaultStmtList* defaultStmtList;
    SwitchStmtType type;
    int cur_id;
    static int GLOBAL_ID;

    static SwitchStmtNode* CreateFromSwitchStmt(ExprNode* expr);
    static SwitchStmtNode* CreateFromSwitchDefaultStmt(ExprNode* expr, CaseDefaultStmtList* defaultStmtList);
    static SwitchStmtNode* CreateFromSwitchDefaultEndswitchStmt(ExprNode* expr, CaseDefaultStmtList* defaultStmtList);

    std::string IdTag();
};