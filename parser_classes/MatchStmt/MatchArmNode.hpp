#include "MatchArmType.cpp"

class MatchArmNode
{
public:
    ExprList* exprList;
    ExprNode* expr;
    MatchArmType type;

    static MatchArmNode* CreateFromMatchArmStmt(ExprList* exprList, ExprNode* expr);
    static MatchArmNode* CreateFromDefaultArmStmt(ExprNode* expr);
    static MatchArmNode* CreateFromDefaultArmWithCommaStmt(ExprNode* expr);
};