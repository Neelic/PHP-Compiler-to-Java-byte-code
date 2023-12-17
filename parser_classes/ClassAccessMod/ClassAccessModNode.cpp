#include "ClassAccessModNode.hpp"

int ClassAccessModNode::GLOBAL_ID = 0;

std::string *ClassAccessModNode::idTag() const {
    auto* tmp = new std::string(std::string("ClassAccessMod") + std::to_string(this->cur_id));
    return tmp;
}

ClassAccessModNode* ClassAccessModNode::CreateNode(ClassAccessMod access_mod)
{
    ClassAccessModNode* tmp = new ClassAccessModNode();
    tmp->access_mod = access_mod;
    tmp->cur_id = ClassAccessModNode::GLOBAL_ID++;
    return tmp;
};

