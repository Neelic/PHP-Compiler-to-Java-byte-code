#include <vector>
#include <string>

class StaticVarNode;

class StaticVarList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<StaticVarNode *> vector;

    static StaticVarList *CreateNode(StaticVarNode *node);
    
    std::string* idTag() const;
};