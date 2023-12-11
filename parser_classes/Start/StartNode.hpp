#include <string>

#include "../Vector_classes/TopStmtList/TopStmtList.hpp"

extern std::string GRAPH_STR;

class StartNode
{
public:
    static int GLOBAL_ID;
    int cur_id;
    TopStmtList *top_stmt_list;

    static StartNode *CreateNode(TopStmtList *top_stmt_list);
    static std::string IdTag();
};