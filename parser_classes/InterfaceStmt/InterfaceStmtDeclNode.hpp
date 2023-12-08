class InterfaceStmtDeclNode
{
public:
    InterfaceExprDefNode* expr_definition;
    InterfaceStmtList* stmt_list;

    static InterfaceStmtDeclNode* Create(InterfaceExprDefNode* expr_definition, InterfaceStmtList* stmt_list);
};