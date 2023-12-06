class MatchStmtNode
{
public:
    ExprNode* expr;
    std::vector<MatchArmNode*>* matchList;

    static MatchStmtNode* CreateFromMatchStmtNode(ExprNode* expr, std::vector<MatchArmNode*>* matchList);
};