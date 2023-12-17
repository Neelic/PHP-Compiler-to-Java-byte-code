#include <vector>
#include <string>

class GlobalVarNode;

class GlobalVarList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<GlobalVarNode*> vector;

  static GlobalVarList *CreateNode(GlobalVarNode *node);
    
    std::string IdTag() const;
};