#include <vector>
#include <string>

class IdListNode
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<std::string*>* vector;

  static IdListNode* CreateNode(std::vector<std::string*>* vector);
  void Insert(std::string* element);
};