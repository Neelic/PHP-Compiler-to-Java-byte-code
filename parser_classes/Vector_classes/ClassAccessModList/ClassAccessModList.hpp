
#ifndef PHP_COMPILER_CLASSACCESSMODLIST
#define PHP_COMPILER_CLASSACCESSMODLIST

#include <vector>
#include <string>

class ClassAccessModNode;

class ClassAccessModList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<ClassAccessModNode *> vector;

    static ClassAccessModList *CreateNode(ClassAccessModNode *node);

    
    std::string* idTag() const;
};

#endif
