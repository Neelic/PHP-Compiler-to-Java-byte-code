#include "../ClassDef/ClassDefType.cpp"
#include <vector>
#include <string>

class IdListNode;

class ClassDefNode
{
public:
    std::string* class_id;
    std::string* extend_id;
    IdListNode* impl_id_list;
    ClassDefType type;
    int cur_id;
    static int GLOBAL_ID;

    static ClassDefNode* CreateFromClassDef(std::string* id);
    static ClassDefNode* CreateFromExtendedDef(std::string* class_id, std::string* extend_id);
    static ClassDefNode* CreateFromImplementDef(std::string* class_id, IdListNode* id_list);
    static ClassDefNode* CreateFromExtendedImplementedDef(std::string* class_id, std::string* extend_id, IdListNode* id_list);

    std::string IdTag();
};