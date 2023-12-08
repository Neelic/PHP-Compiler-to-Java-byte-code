#include <vector>

class ExprNode;

class ExprList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<ExprNode*>* vector;

  static ExprList* CreateNode(std::vector<ExprNode*>* vector);
  void Insert(ExprNode* element);
};