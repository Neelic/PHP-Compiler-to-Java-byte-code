#include "SwitchStmtType.cpp"

class ExprNode;

class SwitchStmtNode
{
public:
    ExprNode* expr;
    std::vector<CaseDefaultStmtNode*>* defaultStmtList;
    SwitchStmtType type;

    static SwitchStmtNode* CreateFromSwitchStmt(ExprNode* expr);
    static SwitchStmtNode* CreateFromSwitchDefaultStmt(ExprNode* expr, std::vector<CaseDefaultStmtNode*>* defaultStmtList);
    static SwitchStmtNode* CreateFromSwitchDefaultEndswitchStmt(ExprNode* expr, std::vector<CaseDefaultStmtNode*>* defaultStmtList);
};