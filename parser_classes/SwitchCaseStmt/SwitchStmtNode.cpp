#include "SwitchStmtNode.hpp"

int SwitchStmtNode::GLOBAL_ID = 0;

std::string SwitchStmtNode::IdTag() {
    return std::string("SwitchStmt") + std::to_string(this->cur_id);
}

SwitchStmtNode* SwitchStmtNode::CreateFromSwitchStmt(ExprNode* expr)
{
    SwitchStmtNode* tmp = new SwitchStmtNode();
    tmp->expr = expr;
    tmp->type = SwitchStmtType::just_switch;
    tmp->cur_id = SwitchStmtNode::GLOBAL_ID++;
    return tmp;;
}

SwitchStmtNode* SwitchStmtNode::CreateFromSwitchDefaultStmt(ExprNode* expr, CaseDefaultStmtList* defaultStmtList)
{
    SwitchStmtNode* tmp = new SwitchStmtNode();
    tmp->expr = expr;
    tmp->defaultStmtList = defaultStmtList;
    tmp->type = SwitchStmtType::switch_default;
    tmp->cur_id = SwitchStmtNode::GLOBAL_ID++;
    return tmp;;
}

SwitchStmtNode* SwitchStmtNode::CreateFromSwitchDefaultEndswitchStmt(ExprNode* expr, CaseDefaultStmtList* defaultStmtList)
{
    SwitchStmtNode* tmp = new SwitchStmtNode();
    tmp->expr = expr;
    tmp->defaultStmtList = defaultStmtList;
    tmp->type = SwitchStmtType::switch_default_endswitch;
    tmp->cur_id = SwitchStmtNode::GLOBAL_ID++;
    return tmp;;
}