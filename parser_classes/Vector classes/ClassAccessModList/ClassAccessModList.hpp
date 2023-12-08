#include <vector>

class ClassAccessModNode;

class ClassAccessModList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<ClassAccessModNode*>* vector;

  static ClassAccessModList* Create(std::vector<ClassAccessModNode*>* vector);
  void Insert(ClassAccessModNode* element);
};