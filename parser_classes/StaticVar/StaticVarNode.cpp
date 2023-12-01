#include "StaticVarNode.hpp"

StaticVarNode* StaticVarNode::CreateFromId(std::string* id)
{
    StaticVarNode* tmp = new StaticVarNode();
    tmp->id = id;
    tmp->type = StaticVarType::var;
    return tmp;
}

StaticVarNode* StaticVarNode::CreateFromIdAssign(std::string* id, ExprNode* expr)
{
    StaticVarNode* tmp = new StaticVarNode();
    tmp->id = id;
    tmp->expr = expr;
    tmp->type = StaticVarType::var;
    return tmp;
}