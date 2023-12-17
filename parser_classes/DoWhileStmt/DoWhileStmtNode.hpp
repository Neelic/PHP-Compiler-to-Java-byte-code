#include <string>

class ExprNode;
class StmtNode;

class DoWhileStmtNode
{
public:
    StmtNode* stmt;
    ExprNode* expr;
    int cur_id;
    static int GLOBAL_ID;

    static DoWhileStmtNode* CreateFromDoWhileStmt(StmtNode* stmt, ExprNode* expr);

    std::string* idTag() const;
};