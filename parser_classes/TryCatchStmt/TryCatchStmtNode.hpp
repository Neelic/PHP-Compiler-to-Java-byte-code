#include <vector>
#include "TryCatchStmtType.cpp"

class TryStmtNode;
class CatchStmtNode;

class TryCatchStmtNode 
{
public:
    TryStmtNode* try_stmt;
    std::vector<CatchStmtNode*>* catch_stmt_list;
    TryCatchStmtType type;

    static TryCatchStmtNode* CreateFromTryCatchStmt(TryStmtNode* try_stmt, std::vector<CatchStmtNode*>* catch_stmt_list);
    static TryCatchStmtNode* CreateFromTryStmt(TryStmtNode* try_stmt);
};