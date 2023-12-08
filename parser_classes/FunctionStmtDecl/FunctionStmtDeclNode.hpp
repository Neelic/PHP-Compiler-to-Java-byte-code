class FunctionDefNode;
class StmtList;

class FunctionStmtDeclNode
{
public:
    FunctionDefNode* function_def;
    StmtList* stmt_list;

    static FunctionStmtDeclNode* CreateNode(FunctionDefNode* function_def, StmtList* stmt_list);
};