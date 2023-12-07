#include "SwitchStmtNode.hpp"

SwitchStmtNode* SwitchStmtNode::CreateFromSwitchStmt(ExprNode* expr)
{
    SwitchStmtNode* tmp = new SwitchStmtNode();
    tmp->expr = expr;
    tmp->type = SwitchStmtType::just_switch;
    return tmp;
}

SwitchStmtNode* SwitchStmtNode::CreateFromSwitchDefaultStmt(ExprNode* expr, CaseDefaultStmtList* defaultStmtList)
{
    SwitchStmtNode* tmp = new SwitchStmtNode();
    tmp->expr = expr;
    tmp->defaultStmtList = defaultStmtList;
    tmp->type = SwitchStmtType::switch_default;
    return tmp;
}

SwitchStmtNode* SwitchStmtNode::CreateFromSwitchDefaultEndswitchStmt(ExprNode* expr, CaseDefaultStmtList* defaultStmtList)
{
    SwitchStmtNode* tmp = new SwitchStmtNode();
    tmp->expr = expr;
    tmp->defaultStmtList = defaultStmtList;
    tmp->type = SwitchStmtType::switch_default_endswitch;
    return tmp;
}