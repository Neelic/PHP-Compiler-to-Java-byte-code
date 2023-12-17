#include <string>
#include "InterfaceExprDefType.cpp"

class IdListNode;

class InterfaceExprDefNode
{
public:
    std::string* id;
    IdListNode* id_extended_list;
    InterfaceExprDefType type;
    int cur_id;
    static int GLOBAL_ID;

    static InterfaceExprDefNode* CreateFromNoExtendedDefinition(std::string* id);
    static InterfaceExprDefNode* CreatedFromDefinitionWithExtended(std::string* id, IdListNode* id_extended_list);

    std::string IdTag();
};