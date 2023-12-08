#include "ClassAccessMod.cpp"

class ClassAccessModNode
{
public:
    ClassAccessMod access_mod;

    static ClassAccessModNode* Create(ClassAccessMod access_mod);
};

ClassAccessModNode* ClassAccessModNode::Create(ClassAccessMod access_mod)
{
    ClassAccessModNode* tmp = new ClassAccessModNode();
    tmp->access_mod = access_mod;
    return tmp;
};