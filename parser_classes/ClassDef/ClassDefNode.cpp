#include "ClassDefNode.hpp"

int ClassDefNode::GLOBAL_ID = 0;

std::string *ClassDefNode::idTag() const {
    auto* tmp = new std::string(std::string("ClassDefNode") + std::to_string(this->cur_id));
    return tmp;
}

ClassDefNode* ClassDefNode::CreateFromClassDef(std::string* id)
{
    ClassDefNode* tmp = new ClassDefNode();
    tmp->class_id = id;
    tmp->type = ClassDefType::class_def_type;
    tmp->cur_id = ClassDefNode::GLOBAL_ID++;
    return tmp;
}

ClassDefNode* ClassDefNode::CreateFromExtendedDef(std::string* class_id, std::string* extend_id)
{
    ClassDefNode* tmp = new ClassDefNode();
    tmp->class_id = class_id;
    tmp->extend_id = extend_id;
    tmp->type = ClassDefType::extends_type;
    tmp->cur_id = ClassDefNode::GLOBAL_ID++;
    return tmp;
}

ClassDefNode* ClassDefNode::CreateFromImplementDef(std::string* class_id, IdListNode* id_list)
{
    ClassDefNode* tmp = new ClassDefNode();
    tmp->class_id = class_id;
    tmp->impl_id_list = id_list;
    tmp->type = ClassDefType::implements_type;
    tmp->cur_id = ClassDefNode::GLOBAL_ID++;
    return tmp;
}

ClassDefNode* ClassDefNode::CreateFromExtendedImplementedDef(std::string* class_id, std::string* extend_id, IdListNode* id_list)
{
    ClassDefNode* tmp = new ClassDefNode();
    tmp->class_id = class_id;
    tmp->extend_id = extend_id;
    tmp->impl_id_list = id_list;
    tmp->type = ClassDefType::extends_implements_type;
    tmp->cur_id = ClassDefNode::GLOBAL_ID++;
    return tmp;
}