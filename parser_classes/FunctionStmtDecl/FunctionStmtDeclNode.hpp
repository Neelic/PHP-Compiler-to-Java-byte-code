class FunctionStmtDeclNode
{
public:
    FunctionDefNode* function_def;
    StmtList* stmt_list;

    static FunctionStmtDeclNode* Create(FunctionDefNode* function_def, StmtList* stmt_list);
};