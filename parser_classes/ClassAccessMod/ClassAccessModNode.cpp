#include "ClassAccessModNode.hpp"

int ClassAccessModNode::GLOBAL_ID = 0;

std::string ClassAccessModNode::IdTag() {
    return std::string("ClassAccessMod") + std::to_string(this->cur_id);
}

ClassAccessModNode* ClassAccessModNode::CreateNode(ClassAccessMod access_mod)
{
    ClassAccessModNode* tmp = new ClassAccessModNode();
    tmp->access_mod = access_mod;
    tmp->cur_id = ClassAccessModNode::GLOBAL_ID++;
    return tmp;
};

