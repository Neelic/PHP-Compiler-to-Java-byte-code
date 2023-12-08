#include <string>
#include "InterfaceExprDefType.cpp"

class IdListNode;

class InterfaceExprDefNode
{
public:
    std::string* id;
    IdListNode* id_extended_list;
    InterfaceExprDefType type;

    static InterfaceExprDefNode* CreateFromNoExtendedDefinition(std::string* id);
    static InterfaceExprDefNode* CreatedFromDefinitionWithExtended(std::string* id, IdListNode* id_extended_list);
};