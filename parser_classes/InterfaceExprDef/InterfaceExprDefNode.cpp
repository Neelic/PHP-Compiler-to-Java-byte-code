#include "InterfaceExprDefNode.hpp"

InterfaceExprDefNode* InterfaceExprDefNode::CreateFromNoExtendedDefinition(std::string* id)
{
    InterfaceExprDefNode* tmp = new InterfaceExprDefNode();
    tmp->id = id;
    tmp->type = InterfaceExprDefType::interface_no_extend_type;
    return tmp;
}

InterfaceExprDefNode* InterfaceExprDefNode::CreatedFromDefinitionWithExtended(std::string* id, IdListNode* id_extended_list)
{
    InterfaceExprDefNode* tmp = new InterfaceExprDefNode();
    tmp->id = id;
    tmp->id_extended_list = id_extended_list;
    tmp->type = InterfaceExprDefType::interface_with_extend_type;
    return tmp;
}