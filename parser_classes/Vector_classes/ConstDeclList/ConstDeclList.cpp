#include "ConstDeclList.hpp"

int ConstDeclList::GLOBAL_ID = 0;

ConstDeclList *ConstDeclList::CreateNode(ConstDeclNode *node) {
    auto *tmp = new ConstDeclList();
    if (node != nullptr)
        tmp->vector.push_back(node);
    tmp->cur_id = ConstDeclList::GLOBAL_ID++;
    return tmp;
}

std::string *ConstDeclList::idTag() const {
    auto* tmp = new std::string(std::string("ConstDeclList") + std::to_string(this->cur_id));
    return tmp;
}