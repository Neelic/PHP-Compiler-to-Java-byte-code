#include "MatchArmType.cpp"

class MatchArmNode
{
public:
    std::vector<ExprNode*>* exprList;
    ExprNode* expr;
    MatchArmType type;

    static MatchArmNode* CreateFromMatchArmStmt(std::vector<ExprNode*>* exprList, ExprNode* expr);
    static MatchArmNode* CreateFromDefaultArmStmt(ExprNode* expr);
    static MatchArmNode* CreateFromDefaultArmWithCommaStmt(ExprNode* expr);
};