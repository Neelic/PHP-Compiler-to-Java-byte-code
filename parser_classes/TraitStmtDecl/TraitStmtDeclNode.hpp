#include <string>

class ClassStmtList;

class TraitStmtDeclNode
{
public:
    std::string* id;
    ClassStmtList* stmt_list;
    int cur_id;
    static int GLOBAL_ID;

    static TraitStmtDeclNode* CreateNode(std::string* id, ClassStmtList* stmt_list);

    std::string* idTag() const;
};