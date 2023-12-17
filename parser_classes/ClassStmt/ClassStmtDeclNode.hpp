#include "ClassStmtDeclType.cpp"
#include <string>

class ClassStmtList;
class ClassDefNode;

class ClassStmtDeclNode
{
public:
    ClassDefNode* class_def;
    ClassStmtList* class_stmt_list;
    ClassStmtDeclType type;
    int cur_id;
    static int GLOBAL_ID;

    static ClassStmtDeclNode* CreateFromNoModDefinition(ClassDefNode* class_def, ClassStmtList* class_stmt_list);
    static ClassStmtDeclNode* CreateFromFinalModDefinition(ClassDefNode* class_def, ClassStmtList* class_stmt_list);
    static ClassStmtDeclNode* CreateFromAbstractModDefinition(ClassDefNode* class_def, ClassStmtList* class_stmt_list);

    std::string* idTag() const;
};