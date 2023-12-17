#include "StartNode.hpp"

int StartNode::GLOBAL_ID = 0;

StartNode *StartNode::CreateNode(TopStmtList *top_stmt_list) {
    auto *tmp = new StartNode();
    tmp->top_stmt_list = top_stmt_list;
    tmp->cur_id = StartNode::GLOBAL_ID++;
    return tmp;
}

std::string * StartNode::idTag() const {
    auto *tmp = new std::string(std::string("Start") + std::to_string(this->cur_id));
    return tmp;
}
