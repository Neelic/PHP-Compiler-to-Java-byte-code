#include "IdListNode.hpp"

int IdListNode::GLOBAL_ID = 0;

IdListNode *IdListNode::CreateNode(std::string *id) {
    auto *tmp = new IdListNode();
    if (id != nullptr)
        tmp->vector.push_back(id);
    tmp->cur_id = IdListNode::GLOBAL_ID++;
    return tmp;
}

std::string IdListNode::IdTag() const {
    return std::string("IdListNode") + std::to_string(this->cur_id);
}