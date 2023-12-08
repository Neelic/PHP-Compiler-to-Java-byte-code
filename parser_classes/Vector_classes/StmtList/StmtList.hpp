#include <vector>

class StmtNode;

class StmtList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<StmtNode*>* vector;

  static StmtList* Create(std::vector<StmtNode*>* vector);
  void Insert(StmtNode* element);
};