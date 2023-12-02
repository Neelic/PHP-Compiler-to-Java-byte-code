class ExprNode;
class StmtNode;

class DoWhileStmtNode
{
public:
    StmtNode* stmt;
    ExprNode* expr;

    static DoWhileStmtNode* CreateFromDoWhileStmt(StmtNode* stmt, ExprNode* expr);
};