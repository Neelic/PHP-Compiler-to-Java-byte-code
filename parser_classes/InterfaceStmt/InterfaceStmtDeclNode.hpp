#include <string>

class InterfaceExprDefNode;
class InterfaceStmtList;

class InterfaceStmtDeclNode
{
public:
    InterfaceExprDefNode* expr_definition;
    InterfaceStmtList* stmt_list;
    int cur_id;
    static int GLOBAL_ID;

    static InterfaceStmtDeclNode* CreateNode(InterfaceExprDefNode* expr_definition, InterfaceStmtList* stmt_list);

    std::string* idTag() const;
};