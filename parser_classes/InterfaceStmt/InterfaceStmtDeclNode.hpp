class InterfaceStmtDeclNode
{
public:
    InterfaceExprDefNode* expr_definition;
    std::vector<InterfaceStmtNode*>* stmt_list;

    static InterfaceStmtDeclNode* Create(InterfaceExprDefNode* expr_definition, std::vector<InterfaceStmtNode*>* stmt_list);
};