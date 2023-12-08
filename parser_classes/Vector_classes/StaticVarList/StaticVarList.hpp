#include <vector>

class StaticVarNode;

class StaticVarList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<StaticVarNode*>* vector;

  static StaticVarList* CreateNode(std::vector<StaticVarNode*>* vector);
  void Insert(StaticVarNode* element);
};