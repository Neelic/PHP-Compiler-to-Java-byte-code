#include "ClassAccessMod.cpp"

class ClassAccessModNode
{
public:
    ClassAccessMod access_mod;

    static ClassAccessModNode* CreateNode(ClassAccessMod access_mod);
};