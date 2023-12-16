#include <string>

class ExprNode;
class MatchArmList;

class MatchStmtNode
{
public:
    ExprNode* expr;
    MatchArmList* matchList;
    int cur_id;
    static int GLOBAL_ID;

    static MatchStmtNode* CreateFromMatchStmtNode(ExprNode* expr, MatchArmList* matchList);

    std::string IdTag();
};