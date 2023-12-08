class TopStmtList;

class StartNode
{
public:
    TopStmtList* top_stmt_list;

    static StartNode* CreateNode(TopStmtList* top_stmt_list);
};

StartNode* StartNode::CreateNode(TopStmtList* top_stmt_list)
{
    StartNode* tmp = new StartNode();
    tmp->top_stmt_list = top_stmt_list;
    return tmp;
}