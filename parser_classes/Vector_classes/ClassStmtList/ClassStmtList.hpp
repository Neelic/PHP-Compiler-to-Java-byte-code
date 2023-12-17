#include <vector>
#include <string>

class ClassStmtNode;

class ClassStmtList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<ClassStmtNode *> vector;
    std::string* idTag() const;

    static ClassStmtList *CreateNode(ClassStmtNode *node);
};