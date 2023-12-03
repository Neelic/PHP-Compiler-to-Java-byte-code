#include "InterfaceExprDefType.cpp"

class InterfaceExprDefNode
{
public:
    std::string* id;
    std::vector<std::string*>* id_extended_list;
    InterfaceExprDefType type;

    static InterfaceExprDefNode* CreateFromNoExtendedDefinition(std::string* id);
    static InterfaceExprDefNode* CreatedFromDefinitionWithExtended(std::string* id, std::vector<std::string*>* id_extended_list);
};