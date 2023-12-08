class TopStmtList;

class StartNode
{
public:
    TopStmtList* top_stmt_list;

    static StartNode* CreateNode(TopStmtList* top_stmt_list);
};