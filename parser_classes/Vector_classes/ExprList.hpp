#include <vector>
#include <string>

class ExprNode;

class ExprList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<ExprNode *> vector;

    static ExprList *CreateNode(ExprNode *node);
    
    std::string* idTag() const;
};