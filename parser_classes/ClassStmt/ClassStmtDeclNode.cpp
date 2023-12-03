#include "ClassStmtDeclNode.hpp"

ClassStmtDeclNode* ClassStmtDeclNode::CreateFromNoModDefinition(ClassDefNode* class_def, std::vector<ClassStmtNode*>* class_stmt_list)
{
    ClassStmtDeclNode* tmp = new ClassStmtDeclNode();
    tmp->class_def = class_def;
    tmp->class_stmt_list = class_stmt_list;
    tmp->type = ClassStmtDeclType::no_modifiers_type;
    return tmp;
}

ClassStmtDeclNode* ClassStmtDeclNode::CreateFromFinalModDefinition(ClassDefNode* class_def, std::vector<ClassStmtNode*>* class_stmt_list)
{
    ClassStmtDeclNode* tmp = new ClassStmtDeclNode();
    tmp->class_def = class_def;
    tmp->class_stmt_list = class_stmt_list;
    tmp->type = ClassStmtDeclType::final_type;
    return tmp;
}

ClassStmtDeclNode* ClassStmtDeclNode::CreateFromAbstractModDefinition(ClassDefNode* class_def, std::vector<ClassStmtNode*>* class_stmt_list)
{
    ClassStmtDeclNode* tmp = new ClassStmtDeclNode();
    tmp->class_def = class_def;
    tmp->class_stmt_list = class_stmt_list;
    tmp->type = ClassStmtDeclType::abstract_type;
    return tmp;
}