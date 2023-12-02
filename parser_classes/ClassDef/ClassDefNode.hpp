#include "../ClassDef/ClassDefType.cpp"
#include <vector>
#include <string>

class ClassDefNode
{
public:
    std::string* class_id;
    std::string* extend_id;
    std::vector<std::string*>* id_list;
    ClassDefType type;

    static ClassDefNode* CreateFromClassDef(std::string* id);
    static ClassDefNode* CreateFromExtendedDef(std::string* class_id, std::string* extend_id);
    static ClassDefNode* CreateFromImplementDef(std::string* class_id, std::vector<std::string*>* id_list);
    static ClassDefNode* CreateFromExtendedImplementedDef(std::string* class_id, std::string* extend_id, std::vector<std::string*>* id_list);
};