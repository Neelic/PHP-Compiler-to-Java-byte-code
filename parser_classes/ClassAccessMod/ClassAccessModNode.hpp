
#ifndef PHP_COMPILER_CLASSACCESSMODNODE
#define PHP_COMPILER_CLASSACCESSMODNODE

#include "ClassAccessMod.cpp"

#include <string>

class ClassAccessModNode
{
public:
    ClassAccessMod access_mod;
    int cur_id;
    static int GLOBAL_ID;

    static ClassAccessModNode* CreateNode(ClassAccessMod access_mod);

    std::string* idTag() const;
};

#endif
