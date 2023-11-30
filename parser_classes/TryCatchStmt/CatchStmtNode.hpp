#include "CatchStmtType.cpp"

class CatchStmtNode
{
public:
    std::string* id_type;
    std::string* id_value;
    std::vector<StmtNode*>* stmtList;
    CatchStmtType type;

    static CatchStmtNode* CreateFromCatchStmt(std::string* id_type, std::string* id_value, std::vector<StmtNode*>* stmtList);
    static CatchStmtNode* CreateFromCatchStmtOnlyType(std::string* id_type, std::vector<StmtNode*>* stmtList);
};