#include <string>

class ClassStmtList;

class TraitStmtDeclNode
{
public:
    std::string* id;
    ClassStmtList* stmt_list;

    static TraitStmtDeclNode* Create(std::string* id, ClassStmtList* stmt_list);
};