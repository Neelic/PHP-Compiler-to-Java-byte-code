#include <string>

class ClassStmtList;

class TraitStmtDeclNode
{
public:
    std::string* id;
    ClassStmtList* stmt_list;

    static TraitStmtDeclNode* CreateNode(std::string* id, ClassStmtList* stmt_list);
};