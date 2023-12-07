class StartNode
{
public:
    TopStmtList* top_stmt_list;

    static StartNode* Create(TopStmtList* top_stmt_list);
};

StartNode* StartNode::Create(TopStmtList* top_stmt_list)
{
    StartNode* tmp = new StartNode();
    tmp->top_stmt_list = top_stmt_list;
    return tmp;
}