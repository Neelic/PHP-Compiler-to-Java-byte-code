#include <vector>

class ConstDeclNode;

class ConstDeclList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<ConstDeclNode*>* vector;

  static ConstDeclList* Create(std::vector<ConstDeclNode*>* vector);
  void Insert(ConstDeclNode* element);
};