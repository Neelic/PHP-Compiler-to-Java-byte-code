#include <vector>

class ClassStmtNode;

class ClassStmtList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<ClassStmtNode*>* vector;

  static ClassStmtList* CreateNode(std::vector<ClassStmtNode*>* vector);
  void Insert(ClassStmtNode* element);
};