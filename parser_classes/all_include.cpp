#include "all_include.hpp"

std::string GRAPH_STR("digraph Tree {\n");

void printTopStmtList(TopStmtList *node, std::string *parentId);
void printTopStmt(TopStmtNode *node, std::string *parentId);
void printStmt(StmtNode *node, std::string *parentId);
void printIfStmt(IfStmtNode *node, std::string *parentId);
void printSwitchStmt(SwitchStmtNode *node, std::string *parentId);
void printStmtList(StmtList *list, std::string *parentId);
void printStaticVarList(StaticVarList *list, std::string *parentId);
void printGlobalVarList(GlobalVarList *list, std::string *parentId);
void printWhileStmt(WhileStmtNode *node, std::string *parentId);
void printDoWhileStmt(DoWhileStmtNode *node, std::string *parentId);
void printForStmt(ForStmtNode *node, std::string *parentId);
void printForEachStmt(ForEachStmtNode *node, std::string *parentId);
void printMatchStmt(MatchStmtNode *node, std::string *parentId);
void printConstDeclList(ConstDeclList *list, std::string *parentId);
void printHtmlStmt(HtmlStmtNode *node, std::string *parentId);
void printExpr(ExprNode *node, std::string *parentId);
void printFunctionStmtDecl(FunctionStmtDeclNode *node, std::string *parentId);
void printClassStmtDecl(ClassStmtDeclNode *node, std::string *parentId);
void printInterfaceStmtDecl(InterfaceStmtDeclNode *node, std::string *parentId);
void printTraitStmtDeclNode(TraitStmtDeclNode *node, std::string *parentId);

void printTreeGraph(StartNode *node) {
    GRAPH_STR += *node->idTag() + " [label=\"Start\"];\n";

    if (node->top_stmt_list != nullptr)
        printTopStmtList(node->top_stmt_list, node->idTag());
}

void printTopStmtList(TopStmtList *node, std::string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Top stmt list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printTopStmt((node->vector)[i], node->idTag());
    }
}

void printTopStmt(TopStmtNode *node, std::string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Top stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  if (node->stmt != nullptr)
    printStmt(node->stmt, node-> idTag());
  if (node->func_stmt_decl != nullptr)
    printFunctionStmtDecl(node->func_stmt_decl, node->idTag());
  if (node->class_stmt_decl != nullptr)
    printClassStmtDecl(node->class_stmt_decl, node->idTag());
  if (node->interface_stmt_decl != nullptr)
    printInterfaceStmtDecl(node->interface_stmt_decl, node->idTag());
  if (node->trait_stmt_decl != nullptr)
    printTraitStmtDeclNode(node->trait_stmt_decl, node->idTag());
}

void printStmt(StmtNode *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"stmt\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  if (node->if_stmt != nullptr)
    printIfStmt(node->if_stmt, node->idTag());
  if (node->switch_stmt != nullptr)
    printSwitchStmt(node->switch_stmt, node->idTag());
  if(node->stmtList != NULL)
    printStmtList(node->stmtList, node->idTag());
  if(node->expr_left != nullptr)
    printExpr(node->expr_left, node->idTag());
  if(node->expr_right != nullptr)
    printExpr(node->expr_right, node->idTag());
  if(node->static_var != NULL)
    printStaticVarList(node->static_var, node->idTag());
  if(node->global_var != NULL)
    printGlobalVarList(node->global_var, node->idTag());
  if(node->while_stmt != nullptr)
    printWhileStmt(node->while_stmt, node->idTag());
  if(node->do_while_stmt != nullptr)
    printDoWhileStmt(node->do_while_stmt, node->idTag());
  if(node->for_stmt != nullptr)
    printForStmt(node->for_stmt, node->idTag());
  if(node->foreach_stmt != nullptr)
    printForEachStmt(node->foreach_stmt, node->idTag());
  if(node->match_stmt != nullptr)
    printMatchStmt(node->match_stmt, node->idTag());
  if(node->const_decl != NULL)
    printConstDeclList(node->const_decl, node->idTag());
  if (node->html_stmt != nullptr)
    printHtmlStmt(node->html_stmt, node->idTag());
};

void printIfStmt(IfStmtNode *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"If_stmt\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
  
  if (node->expr != nullptr)
    printExpr(node->expr, node->idTag());
  if (node->stmt_main != nullptr)
    printStmt(node->stmt_main, node->idTag());
  if (node->stmt_else != nullptr)
    printStmt(node->stmt_else, node->idTag());
  if (node->stmtListMain != NULL)
    printStmtList(node->stmtListMain, node->idTag());
  if (node->stmtListElse != NULL)
    printStmtList(node->stmtListElse, node->idTag());
};

void printSwitchStmt(SwitchStmtNode *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"Switch_stmt\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
};

