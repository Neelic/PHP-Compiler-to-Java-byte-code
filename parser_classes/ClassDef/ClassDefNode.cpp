#include "ClassDefNode.hpp"

ClassDefNode* ClassDefNode::CreateFromClassDef(std::string* id)
{
    ClassDefNode* tmp = new ClassDefNode();
    tmp->class_id = id;
    tmp->type = ClassDefType::class_def_type;
    return tmp;
}

ClassDefNode* ClassDefNode::CreateFromExtendedDef(std::string* class_id, std::string* extend_id)
{
    ClassDefNode* tmp = new ClassDefNode();
    tmp->class_id = class_id;
    tmp->extend_id = extend_id;
    tmp->type = ClassDefType::extends_type;
    return tmp;
}

ClassDefNode* ClassDefNode::CreateFromImplementDef(std::string* class_id, IdListNode* id_list)
{
    ClassDefNode* tmp = new ClassDefNode();
    tmp->class_id = class_id;
    tmp->impl_id_list = id_list;
    tmp->type = ClassDefType::implements_type;
    return tmp;
}

ClassDefNode* ClassDefNode::CreateFromExtendedImplementedDef(std::string* class_id, std::string* extend_id, IdListNode* id_list)
{
    ClassDefNode* tmp = new ClassDefNode();
    tmp->class_id = class_id;
    tmp->extend_id = extend_id;
    tmp->impl_id_list = id_list;
    tmp->type = ClassDefType::extends_implements_type;
    return tmp;
}