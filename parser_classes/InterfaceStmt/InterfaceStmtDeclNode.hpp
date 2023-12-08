class InterfaceExprDefNode;
class InterfaceStmtList;

class InterfaceStmtDeclNode
{
public:
    InterfaceExprDefNode* expr_definition;
    InterfaceStmtList* stmt_list;

    static InterfaceStmtDeclNode* CreateNode(InterfaceExprDefNode* expr_definition, InterfaceStmtList* stmt_list);
};