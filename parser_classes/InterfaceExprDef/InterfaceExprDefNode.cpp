#include "InterfaceExprDefNode.hpp"

int InterfaceExprDefNode::GLOBAL_ID = 0;

std::string *InterfaceExprDefNode::idTag() const {
    auto* tmp = new std::string(std::string("InterfaceExprDef") + std::to_string(this->cur_id));
    return tmp;
}

InterfaceExprDefNode* InterfaceExprDefNode::CreateFromNoExtendedDefinition(std::string* id)
{
    InterfaceExprDefNode* tmp = new InterfaceExprDefNode();
    tmp->id = id;
    tmp->type = InterfaceExprDefType::interface_no_extend_type;
    tmp->cur_id = InterfaceExprDefNode::GLOBAL_ID++;
    return tmp;
}

InterfaceExprDefNode* InterfaceExprDefNode::CreatedFromDefinitionWithExtended(std::string* id, IdListNode* id_extended_list)
{
    InterfaceExprDefNode* tmp = new InterfaceExprDefNode();
    tmp->id = id;
    tmp->id_extended_list = id_extended_list;
    tmp->type = InterfaceExprDefType::interface_with_extend_type;
    tmp->cur_id = InterfaceExprDefNode::GLOBAL_ID++;
    return tmp;
}