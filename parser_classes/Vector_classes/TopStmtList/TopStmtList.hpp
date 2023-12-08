#include <vector>

class TopStmtNode;

class TopStmtList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<TopStmtNode*>* vector;

  static TopStmtList* CreateNode(std::vector<TopStmtNode*>* vector);
  void Insert(TopStmtNode* element);
};