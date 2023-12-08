#include <vector>

class ExprFuncNode;

class ExprFuncList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<ExprFuncNode*>* vector;

  static ExprFuncList* Create(std::vector<ExprFuncNode*>* vector);
  void Insert(ExprFuncNode* element);
};