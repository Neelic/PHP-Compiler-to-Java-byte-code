#include <vector>
#include <string>

#ifndef TOP_STMT_LIST_H
#define TOP_STMT_LIST_H

#include "../../TopStmt/TopStmtNode.hpp"

class TopStmtNode;

extern std::string GRAPH_STR;

class TopStmtList
{
public:
  static int GLOBAL_ID;
  int cur_id;
  std::vector<TopStmtNode*>* vector;

  static TopStmtList* CreateNode(std::vector<TopStmtNode*>* vector);
  void Insert(TopStmtNode* element);
  
  std::string IdTag();
};

#endif