class TryStmtNode
{
public:
    std::vector<StmtList*>* stmtList;

    static TryStmtNode* CreateFromTryStmt(std::vector<StmtList*>* stmtList);
}