#include <vector>
#include <string>

class ClassStmtNode;

class ClassStmtList {
public:
    static int GLOBAL_ID;
    int cur_id;
    std::vector<ClassStmtNode *> vector;
    std::string IdTag() const;

    static ClassStmtList *CreateNode(ClassStmtNode *node);
};