#include "all_include.hpp"

std::string GRAPH_STR("digraph Tree {\n"); 

static int VALUE_ID; // Для тегов узлов с конечным значением
int VALUE_ID = 0;

void printTopStmtList(TopStmtList *node, std::string *parentId);
void printTopStmt(TopStmtNode *node, std::string *parentId);
void printStmt(StmtNode *node, std::string *parentId);
void printIfStmt(IfStmtNode *node, std::string *parentId);
void printSwitchStmt(SwitchStmtNode *node, std::string *parentId);
void printCaseDefaultStmtList(CaseDefaultStmtList *node, std::string *parentId);
void printCaseDefaultStmt(CaseDefaultStmtNode *node, std::string *parentId);
void printStmtList(StmtList *node, std::string *parentId);
void printStaticVarList(StaticVarList *node, std::string *parentId);
void printStaticVar(StaticVarNode *node, std::string *parentId);
void printGlobalVarList(GlobalVarList *node, std::string *parentId);
void printWhileStmt(WhileStmtNode *node, std::string *parentId);
void printDoWhileStmt(DoWhileStmtNode *node, std::string *parentId);
void printForStmt(ForStmtNode *node, std::string *parentId);
void printForEachStmt(ForEachStmtNode *node, std::string *parentId);
void printMatchStmt(MatchStmtNode *node, std::string *parentId);
void printConstDeclList(ConstDeclList *node, std::string *parentId);
void printHtmlStmt(HtmlStmtNode *node, std::string *parentId);
void printExpr(ExprNode *node, std::string *parentId, std::string *arrowLabel);
void printFunctionStmtDecl(FunctionStmtDeclNode *node, std::string *parentId);
void printClassStmtDecl(ClassStmtDeclNode *node, std::string *parentId);
void printInterfaceStmtDecl(InterfaceStmtDeclNode *node, std::string *parentId);
void printTraitStmtDeclNode(TraitStmtDeclNode *node, std::string *parentId);
void printGetValue(GetValueNode *node, std::string *parentId);
void printStringValueNode(std::string *value, std::string *parentId, std::string *arrowLabel); // Печатает узел со строковым значением

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

//Возможно переделать
void printStmt(StmtNode *node, std::string *parentId) 
{
  GRAPH_STR += *node->idTag() + " [label=\"stmt\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  if (node->if_stmt != nullptr)
    printIfStmt(node->if_stmt, node->idTag());
  if (node->switch_stmt != nullptr)
    printSwitchStmt(node->switch_stmt, node->idTag());
  if(node->stmtList != nullptr)
    printStmtList(node->stmtList, node->idTag());
  if(node->expr_left != nullptr)
    printExpr(node->expr_left, node->idTag(), new std::string("left")); //TODO: В зависимости от node->type передавать разные значения для label
  if(node->expr_right != nullptr)
    printExpr(node->expr_right, node->idTag(), new std::string("right")); //TODO: В зависимости от node->type передавать разные значения для label
  if(node->static_var != nullptr)
    printStaticVarList(node->static_var, node->idTag());
  if(node->global_var != nullptr)
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
  if(node->const_decl != nullptr)
    printConstDeclList(node->const_decl, node->idTag());
  if (node->html_stmt != nullptr)
    printHtmlStmt(node->html_stmt, node->idTag());
};

void printIfStmt(IfStmtNode *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"If stmt\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
  
  if (node->expr != nullptr)
    printExpr(node->expr, node->idTag(), new std::string("condition"));
  if (node->stmt_main != nullptr)
    printStmt(node->stmt_main, node->idTag());
  if (node->stmt_else != nullptr)
    printStmt(node->stmt_else, node->idTag());
  if (node->stmtListMain != nullptr)
    printStmtList(node->stmtListMain, node->idTag());
  if (node->stmtListElse != nullptr)
    printStmtList(node->stmtListElse, node->idTag());
};

void printSwitchStmt(SwitchStmtNode *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"Switch stmt\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  if (node->expr != nullptr)
    printExpr(node->expr, node->idTag(), new std::string("param"));
  if (node->defaultStmtList != nullptr)
    printCaseDefaultStmtList(node->defaultStmtList, node->idTag());
};

void printCaseDefaultStmtList(CaseDefaultStmtList *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"Case default stmt list\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  for (int i = 0; i < node->vector.size(); i++) {
      printCaseDefaultStmt((node->vector)[i], node->idTag());
  }
}

void printCaseDefaultStmt(CaseDefaultStmtNode *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"Switch stmt\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  if (node->expr != nullptr)
    printExpr(node->expr, node->idTag(), new std::string("condition"));
  if (node->stmtList != nullptr)
    printStmtList(node->stmtList, node->idTag());
};

void printStmtList(StmtList *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"Stmt list\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  for (int i = 0; i < node->vector.size(); i++) {
      printStmt((node->vector)[i], node->idTag());
  }
};

void printStaticVarList(StaticVarList *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"Static var list\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  for (int i = 0; i < node->vector.size(); i++) {
      printStaticVar((node->vector)[i], node->idTag());
  }
};

void printStaticVar(StaticVarNode *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"Switch stmt\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  if (node->id != nullptr)
    printStringValueNode(node->id, node->idTag(), new std::string(""));
  if(node->expr != nullptr)
    printExpr(node->expr, node->idTag(), new std::string(""));
}

//Пока только два варианта для примера
void printExpr(ExprNode *node, std::string *parentId, std::string *arrowLabel)
{
  switch (node->exprType)
  {
  case ExprType::int_val: //Если просто значение, может просто его и печатать? А то получится узел ради узла
    GRAPH_STR += *node->idTag() + " [label=\"" + std::to_string(node->int_val) + "\"];\n";
    break;

  case ExprType::string_val:
    GRAPH_STR += *node->idTag() + " [label=\" \\\"" + *node->string_val + "\\\" \"];\n";
    break;
  
  case ExprType::this_keyword:
    GRAPH_STR += *node->idTag() + " [label=\" This \"];\n";
    break;

  case ExprType::self_keyword:
    GRAPH_STR += *node->idTag() + " [label=\" Self \"];\n";
    break;

  case ExprType::parent_keyword:
    GRAPH_STR += *node->idTag() + " [label=\" Parent \"];\n";
    break;

  case ExprType::variable:
    GRAPH_STR += *node->idTag() + " [label=\"Variable\"];\n";
    printGetValue(node->get_value, node->idTag());
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    break;

  case ExprType::constant:
    GRAPH_STR += *node->idTag() + " [label=\" \\\"" + *node->id + "\\\" \"];\n";
    break;

  case ExprType::assign_op:
    GRAPH_STR += *node->idTag() + " [label=\"=\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::assign_ref_op:
    GRAPH_STR += *node->idTag() + " [label=\"assign ref\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::int_cast: //Если операция более сложная, пишем название операции в лейбл
    GRAPH_STR += *node->idTag() + " [label=\"Int cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::float_cast: //Если операция более сложная, пишем название операции в лейбл
    GRAPH_STR += *node->idTag() + " [label=\"Float cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::string_cast: //Если операция более сложная, пишем название операции в лейбл
    GRAPH_STR += *node->idTag() + " [label=\"String cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::array_cast: //Если операция более сложная, пишем название операции в лейбл
    GRAPH_STR += *node->idTag() + " [label=\"Array cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::object_cast: //Если операция более сложная, пишем название операции в лейбл
    GRAPH_STR += *node->idTag() + " [label=\"Object cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::bool_cast: //Если операция более сложная, пишем название операции в лейбл
    GRAPH_STR += *node->idTag() + " [label=\"Bool cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::class_inst_field_ref_op:
    GRAPH_STR += *node->idTag() + " [label=\"->\"];\n";
    if (node->get_value != nullptr)
      printGetValue(node->get_value, node->idTag());
    printExpr(node->left, node->idTag(), new std::string(""));
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    break;

  case ExprType::class_inst_field_by_ref_op:
    GRAPH_STR += *node->idTag() + " [label=\"->\"];\n";
    if (node->get_value != nullptr)
      printGetValue(node->get_value, node->idTag());
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;
    break;
  
  case ExprType::plus_op: // Если операция с одним символом, просто пишем операцию в лейбле
    GRAPH_STR += *node->idTag() + " [label=\"+\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;
  }

  GRAPH_STR += *node->idTag() + " -> " + *parentId + "[label=\"" + *arrowLabel + "\"];\n";
};

void printStringValueNode(std::string *value, std::string *parentId, std::string *arrowLabel)
{
  std::string tag("VAL_" + std::to_string(VALUE_ID++));

  GRAPH_STR += tag + " [label=\"" + *value + "\"];\n";
  GRAPH_STR += tag + " -> " + *parentId + " [label=\"" + *arrowLabel + "\"];\n";
};