#include <vector>

class GetValueFuncNode;

class GetValueFuncList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<GetValueFuncNode *> vector;

    static GetValueFuncList *CreateNode(GetValueFuncNode *node);
};