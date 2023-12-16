#include "ClassStmtDeclNode.hpp"

int ClassStmtDeclNode::GLOBAL_ID = 0;

std::string ClassStmtDeclNode::IdTag() {
    return std::string("ClassStmtDecl") + std::to_string(this->cur_id);
}

ClassStmtDeclNode* ClassStmtDeclNode::CreateFromNoModDefinition(ClassDefNode* class_def, ClassStmtList* class_stmt_list)
{
    ClassStmtDeclNode* tmp = new ClassStmtDeclNode();
    tmp->class_def = class_def;
    tmp->class_stmt_list = class_stmt_list;
    tmp->type = ClassStmtDeclType::no_modifiers_type;
    tmp->cur_id = ClassStmtDeclNode::GLOBAL_ID++;
    return tmp;
}

ClassStmtDeclNode* ClassStmtDeclNode::CreateFromFinalModDefinition(ClassDefNode* class_def, ClassStmtList* class_stmt_list)
{
    ClassStmtDeclNode* tmp = new ClassStmtDeclNode();
    tmp->class_def = class_def;
    tmp->class_stmt_list = class_stmt_list;
    tmp->type = ClassStmtDeclType::final_type;
    tmp->cur_id = ClassStmtDeclNode::GLOBAL_ID++;
    return tmp;
}

ClassStmtDeclNode* ClassStmtDeclNode::CreateFromAbstractModDefinition(ClassDefNode* class_def, ClassStmtList* class_stmt_list)
{
    ClassStmtDeclNode* tmp = new ClassStmtDeclNode();
    tmp->class_def = class_def;
    tmp->class_stmt_list = class_stmt_list;
    tmp->type = ClassStmtDeclType::abstract_type;
    tmp->cur_id = ClassStmtDeclNode::GLOBAL_ID++;
    return tmp;
}