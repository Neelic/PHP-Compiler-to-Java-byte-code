#include <vector>

class GlobalVarNode;

class GlobalVarList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<GlobalVarNode*>* vector;

  static GlobalVarList* Create(std::vector<GlobalVarNode*>* vector);
  void Insert(GlobalVarNode* element);
};