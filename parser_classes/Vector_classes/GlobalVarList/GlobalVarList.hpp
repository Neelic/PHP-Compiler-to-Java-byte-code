#ifndef PHP_COMPILER_GLOBAL_VAR_LIST
#define PHP_COMPILER_GLOBAL_VAR_LIST

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
    
    std::string* idTag() const;
};

#endif
