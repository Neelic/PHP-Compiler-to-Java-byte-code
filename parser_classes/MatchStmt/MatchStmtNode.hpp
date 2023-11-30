class MatchStmtNode
{
public:
    ExprNode* expr;
    std::vector<MatchStmtNode*>* matchList;

    static MatchStmtNode* CreateFromMatchStmtNode(ExprNode* expr, std::vector<MatchStmtNode*>* matchList);
}