class FunctionStmtDeclNode
{
public:
    FunctionDefNode* function_def;
    std::vector<StmtNode*>* stmt_list;

    static FunctionStmtDeclNode* Create(FunctionDefNode* function_def, std::vector<StmtNode*>* stmt_list);
};