#include <string>

class FunctionDefNode;
class StmtList;

class FunctionStmtDeclNode
{
public:
    FunctionDefNode* function_def;
    StmtList* stmt_list;
    int cur_id;
    static int GLOBAL_ID;

    static FunctionStmtDeclNode* CreateNode(FunctionDefNode* function_def, StmtList* stmt_list);

    std::string* idTag() const;
};