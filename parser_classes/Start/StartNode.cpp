class StartNode
{
public:
    std::vector<TopStmtNode*>* top_stmt_list;

    static StartNode* Create(std::vector<TopStmtNode*>* top_stmt_list);
};

StartNode* StartNode::Create(std::vector<TopStmtNode*>* top_stmt_list)
{
    StartNode* tmp = new StartNode();
    tmp->top_stmt_list = top_stmt_list;
    return tmp;
}