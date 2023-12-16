#include "StaticVarNode.hpp"

int StaticVarNode::GLOBAL_ID = 0;

std::string StaticVarNode::IdTag() {
    return std::string("StaticVar") + std::to_string(this->cur_id);
}

StaticVarNode* StaticVarNode::CreateFromId(std::string* id)
{
    StaticVarNode* tmp = new StaticVarNode();
    tmp->id = id;
    tmp->type = StaticVarType::var;
    tmp->cur_id = StaticVarNode::GLOBAL_ID++;
    return tmp;
}

StaticVarNode* StaticVarNode::CreateFromIdAssign(std::string* id, ExprNode* expr)
{
    StaticVarNode* tmp = new StaticVarNode();
    tmp->id = id;
    tmp->expr = expr;
    tmp->type = StaticVarType::var;
    tmp->cur_id = StaticVarNode::GLOBAL_ID++;
    return tmp;
}