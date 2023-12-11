#include "StartNode.hpp"

int StartNode::GLOBAL_ID = 0;

StartNode* StartNode::CreateNode(TopStmtList* top_stmt_list)
{
    StartNode* tmp = new StartNode();
    tmp->top_stmt_list = top_stmt_list;
    tmp->cur_id = StartNode::GLOBAL_ID++;

    return tmp;
}

std::string StartNode::IdTag()
{
    return std::string("Start");
}
