#include <vector>

class InterfaceStmtNode;

class InterfaceStmtList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<InterfaceStmtNode*> vector;

  static InterfaceStmtList *CreateNode(InterfaceStmtNode *node);
};