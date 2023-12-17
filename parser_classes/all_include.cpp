#include "all_include.hpp"

std::string GRAPH_STR("digraph Tree {\n");

void printTopStmtList(TopStmtList *node, StartNode *parent);
void printTopStmt(TopStmtNode *node, TopStmtList *parent);
void printStmt(StmtNode *node, std::string id_tag);
void printIfStmt(IfStmtNode *node, std::string id_tag);
void printSwitchStmt(SwitchStmtNode *node, std::string id_tag);
void printStmtList(StmtList *list, std::string id_tag);
void printStaticVarList(StaticVarList *list, std::string id_tag);
void printGlobalVarList(GlobalVarList *list, std::string id_tag);
void printWhileStmt(WhileStmtNode *node, std::string id_tag);
void printDoWhileStmt(DoWhileStmtNode *node, std::string id_tag);
void printForStmt(ForStmtNode *node, std::string id_tag);
void printForEachStmt(ForEachStmtNode *node, std::string id_tag);
void printMatchStmt(MatchStmtNode *node, std::string id_tag);
void printConstDeclList(ConstDeclList *list, std::string id_tag);
void printHtmlStmt(HtmlStmtNode *node, std::string id_tag);
void printExpr(ExprNode *node, std::string id_tag);
void printFunctionStmtDecl(FunctionStmtDeclNode *node, std::string id_tag);
void printClassStmtDecl(ClassStmtDeclNode *node, std::string id_tag);
void printInterfaceStmtDecl(InterfaceStmtDeclNode *node, std::string id_tag);
void printTraitStmtDeclNode(TraitStmtDeclNode *node, std::string id_tag);

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
    printStmt(node->stmt, node->IdTag());
  if (node->func_stmt_decl != nullptr)
    printFunctionStmtDecl(node->func_stmt_decl, node->IdTag());
  if (node->class_stmt_decl != nullptr)
    printClassStmtDecl(node->class_stmt_decl, node->IdTag());
  if (node->interface_stmt_decl != nullptr)
    printInterfaceStmtDecl(node->interface_stmt_decl, node->IdTag());
  if (node->trait_stmt_decl != nullptr)
    printTraitStmtDeclNode(node->trait_stmt_decl, node->IdTag());
}

void printStmt(StmtNode *node, std::string id_tag)
{
  GRAPH_STR += node->IdTag() + " [label=\"stmt\"];\n";
  GRAPH_STR += node->IdTag() + " -> " + id_tag + "\n";

  if (node->if_stmt != nullptr)
    printIfStmt(node->if_stmt, node->IdTag());
  if (node->switch_stmt != nullptr)
    printSwitchStmt(node->switch_stmt, node->IdTag());
  if(node->stmtList != NULL)
    printStmtList(node->stmtList, node->IdTag());
  if(node->expr_left != nullptr)
    printExpr(node->expr_left, node->IdTag());
  if(node->expr_right != nullptr)
    printExpr(node->expr_right, node->IdTag());
  if(node->static_var != NULL)
    printStaticVarList(node->static_var, node->IdTag());
  if(node->global_var != NULL)
    printGlobalVarList(node->global_var, node->IdTag());
  if(node->while_stmt != nullptr)
    printWhileStmt(node->while_stmt, node->IdTag());
  if(node->do_while_stmt != nullptr)
    printDoWhileStmt(node->do_while_stmt, node->IdTag());
  if(node->for_stmt != nullptr)
    printForStmt(node->for_stmt, node->IdTag());
  if(node->foreach_stmt != nullptr)
    printForEachStmt(node->foreach_stmt, node->IdTag());
  if(node->match_stmt != nullptr)
    printMatchStmt(node->match_stmt, node->IdTag());
  if(node->const_decl != NULL)
    printConstDeclList(node->const_decl, node->IdTag());
  if (node->html_stmt != nullptr)
    printHtmlStmt(node->html_stmt, node->IdTag());
};

void printIfStmt(IfStmtNode *node, std::string id_tag)
{
  GRAPH_STR += node->IdTag() + " [label=\"stmt\"];\n";
  GRAPH_STR += node->IdTag() + " -> " + id_tag + "\n";
  
  if (node->expr != nullptr)
    printExpr(node->expr, node->IdTag());
  if (node->stmt_main != nullptr)
    printStmt(node->stmt_main, node->IdTag());
  if (node->stmt_else != nullptr)
    printStmt(node->stmt_else, node->IdTag());
  if (node->stmtListMain != NULL)
    printStmtList(node->stmtListMain, node->IdTag());
  if (node->stmtListElse != NULL)
    printStmtList(node->stmtListElse, node->IdTag());
};

void printSwitchStmt(SwitchStmtNode *node, std::string id_tag)
{
  GRAPH_STR += node->IdTag() + " [label=\"stmt\"];\n";
  GRAPH_STR += node->IdTag() + " -> " + id_tag + "\n";
};

