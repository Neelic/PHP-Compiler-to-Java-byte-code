#include <vector>
#include <string>

class MatchArmNode;

class MatchArmList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<MatchArmNode *> vector;

    static MatchArmList *CreateNode(MatchArmNode *node);
    
    std::string IdTag() const;
};