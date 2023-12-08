#include <vector>

class GetValueFuncNode;

class GetValueFuncList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<GetValueFuncNode*>* vector;

  static GetValueFuncList* Create(std::vector<GetValueFuncNode*>* vector);
  void Insert(GetValueFuncNode* element);
};