#include "ClassStmtDeclType.cpp"

class ClassStmtList;
class ClassDefNode;

class ClassStmtDeclNode
{
public:
    ClassDefNode* class_def;
    ClassStmtList* class_stmt_list;
    ClassStmtDeclType type;

    static ClassStmtDeclNode* CreateFromNoModDefinition(ClassDefNode* class_def, ClassStmtList* class_stmt_list);
    static ClassStmtDeclNode* CreateFromFinalModDefinition(ClassDefNode* class_def, ClassStmtList* class_stmt_list);
    static ClassStmtDeclNode* CreateFromAbstractModDefinition(ClassDefNode* class_def, ClassStmtList* class_stmt_list);
};