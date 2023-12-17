#include "MatchArmType.cpp"
#include <string>

class ExprList;
class ExprNode;

class MatchArmNode
{
public:
    ExprList* exprList;
    ExprNode* expr;
    MatchArmType type;
    int cur_id;
    static int GLOBAL_ID;

    static MatchArmNode* CreateFromMatchArmStmt(ExprList* exprList, ExprNode* expr);
    static MatchArmNode* CreateFromDefaultArmStmt(ExprNode* expr);
    static MatchArmNode* CreateFromDefaultArmWithCommaStmt(ExprNode* expr);

    std::string* idTag() const;
};