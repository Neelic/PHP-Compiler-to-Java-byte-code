#include "ClassAccessModNode.hpp"

ClassAccessModNode* ClassAccessModNode::CreateNode(ClassAccessMod access_mod)
{
    ClassAccessModNode* tmp = new ClassAccessModNode();
    tmp->access_mod = access_mod;
    return tmp;
};