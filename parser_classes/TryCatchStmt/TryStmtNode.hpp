#include <vector>

class StmtNode;

class TryStmtNode
{
public:
    std::vector<StmtNode*>* stmtList;

    static TryStmtNode* CreateFromTryStmt(std::vector<StmtNode*>* stmtList);
};