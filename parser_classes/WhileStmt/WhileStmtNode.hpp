#include "WhileStmtType.cpp"
#include <string>

class ExprNode;
class StmtNode;
class StmtList;

class WhileStmtNode
{
public:
    ExprNode* expr;
    StmtNode* stmt;
    StmtList* stmtList;
    WhileStmtType type;
    int cur_id;
    static int GLOBAL_ID;

    static WhileStmtNode* CreateFromWhileStmt(ExprNode* expr, StmtNode* stmt);
    static WhileStmtNode* CreateFromEndWhileStmt(ExprNode* expr, StmtList* stmtList);

    std::string* idTag() const;
};