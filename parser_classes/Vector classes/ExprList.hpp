#include <vector>

class ExprNode;

class ExprList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<ExprNode*>* vector;

  static ExprList* Create(std::vector<ExprNode*>* vector);
  void Insert(ExprNode* element);
};