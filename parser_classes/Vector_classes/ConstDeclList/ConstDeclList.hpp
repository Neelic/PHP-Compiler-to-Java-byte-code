#include <vector>
#include <string>

class ConstDeclNode;

class ConstDeclList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<ConstDeclNode *> vector;

    static ConstDeclList *CreateNode(ConstDeclNode *node);
    
    std::string IdTag() const;
};