#include <vector>

class StmtNode;

#ifndef STMT_LIST_H
#define STMT_LIST_H
#include <string>

class StmtList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<StmtNode*>* vector;

  static StmtList* CreateNode(std::vector<StmtNode*>* vector);
  void Insert(StmtNode* element);

  std::string IdTag();
};

#endif