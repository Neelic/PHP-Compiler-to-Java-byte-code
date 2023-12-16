#include "all_include.hpp"

std::string GRAPH_STR("digraph Tree {\n");

void printTopStmtList(TopStmtList *node, StartNode *parent);
void printTopStmt(TopStmtNode *node, TopStmtList *parent);
void printStmtFromTopStmt(StmtNode *node, TopStmtNode *parent);

void printTreeGraph(StartNode *node)
{
  GRAPH_STR += node->IdTag() + " [label=\"Start\"];\n";

  if (node->top_stmt_list != NULL)
    printTopStmtList(node->top_stmt_list, node);
}

void printTopStmtList(TopStmtList *node, StartNode *parent)
{
  GRAPH_STR += node->IdTag() + " [label=\"Top stmt list\"]\n";
  GRAPH_STR += node->IdTag() + " -> " + parent->IdTag() + "\n";

  for (int i = 0; i < node->vector.size(); i++)
  {
    printTopStmt((node->vector)[i], node);
  }
}

void printTopStmt(TopStmtNode *node, TopStmtList *parent)
{
  GRAPH_STR += node->IdTag() + " [label=\"Top stmt\"];\n";
  GRAPH_STR += node->IdTag() + " -> " + parent->IdTag() + "\n";

  if (node->stmt != nullptr)
    printStmtFromTopStmt(node->stmt, node);
}

void printStmtFromTopStmt(StmtNode *node, TopStmtNode *parent)
{
  GRAPH_STR += node->IdTag() + " [label=\"stmt\"];\n";
  GRAPH_STR += node->IdTag() + " -> " + parent->IdTag() + "\n";
}