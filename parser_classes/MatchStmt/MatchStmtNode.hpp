class ExprNode;
class MatchArmList;

class MatchStmtNode
{
public:
    ExprNode* expr;
    MatchArmList* matchList;

    static MatchStmtNode* CreateFromMatchStmtNode(ExprNode* expr, MatchArmList* matchList);
};