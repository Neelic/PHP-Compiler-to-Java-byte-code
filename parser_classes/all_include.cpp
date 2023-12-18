#include "all_include.hpp"

std::string GRAPH_STR("digraph Tree {\n"); 

static int VALUE_ID = 0; // Для тегов узлов с конечным значением
//int VALUE_ID = 0;

void printTopStmtList(TopStmtList *node, std::string *parentId);
void printTopStmt(TopStmtNode *node, std::string *parentId);
void printStmt(StmtNode *node, std::string *parentId, std::string *arrowLabel);
void printIfStmt(IfStmtNode *node, std::string *parentId);
void printSwitchStmt(SwitchStmtNode *node, std::string *parentId);
void printCaseDefaultStmtList(CaseDefaultStmtList *node, std::string *parentId);
void printCaseDefaultStmt(CaseDefaultStmtNode *node, std::string *parentId);
void printStmtList(StmtList *node, std::string *parentId, std::string *arrowLabel);
void printStaticVarList(StaticVarList *node, std::string *parentId);
void printStaticVar(StaticVarNode *node, std::string *parentId);
void printGlobalVarList(GlobalVarList *node, std::string *parentId);
void printGlobalVar(GlobalVarNode *node, std::string *parentId);
void printWhileStmt(WhileStmtNode *node, std::string *parentId);
void printDoWhileStmt(DoWhileStmtNode *node, std::string *parentId);
void printForStmt(ForStmtNode *node, std::string *parentId);
void printForEachStmt(ForEachStmtNode *node, std::string *parentId);
void printMatchStmt(MatchStmtNode *node, std::string *parentId);
void printConstDeclList(ConstDeclList *node, std::string *parentId);
void printHtmlStmt(HtmlStmtNode *node, std::string *parentId);
void printExpr(ExprNode *node, std::string *parentId, std::string *arrowLabel);
void printExprList(ExprList *node, std::string *parentId);
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
    printStmt(node->stmt, node-> idTag(), new std::string(""));
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
void printStmt(StmtNode *node, std::string *parentId, std::string *arrowLabel) 
{
  switch (node->type)
  {
  case StmtType::throw_stmt:
    GRAPH_STR += *node->idTag() + " [label=\"Throw\"];\n";
    printExpr(node->expr_left, node->idTag(), new std::string(""));
    break;

  case StmtType::return_stmt:
    GRAPH_STR += *node->idTag() + " [label=\"Return\"];\n";
    printExpr(node->expr_left, node->idTag(), new std::string(""));
    break;

  case StmtType::break_stmt:
    GRAPH_STR += *node->idTag() + " [label=\"Break\"];\n";
    break;

  case StmtType::t_echo_stmt:
    GRAPH_STR += *node->idTag() + " [label=\"t-echo\"];\n";
    printExpr(node->expr_left, node->idTag(), new std::string(""));
    break;
  
  case StmtType::continue_stmt:
    GRAPH_STR += *node->idTag() + " [label=\"Continue\"];\n";
    break;

  default:
    GRAPH_STR += *node->idTag() + " [label=\"stmt\"];\n";

    if (node->if_stmt != nullptr)
    printIfStmt(node->if_stmt, node->idTag());
    if (node->switch_stmt != nullptr)
      printSwitchStmt(node->switch_stmt, node->idTag());
    if(node->stmtList != nullptr)
      printStmtList(node->stmtList, node->idTag(), new std::string(""));
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
    break;
  }

  GRAPH_STR += *node->idTag() + " -> " + *parentId + "[label=\"" + *arrowLabel + "\"];\n";
};

void printIfStmt(IfStmtNode *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"If stmt\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
  
  if (node->expr != nullptr)
    printExpr(node->expr, node->idTag(), new std::string("condition"));
  if (node->stmt_main != nullptr)
    printStmt(node->stmt_main, node->idTag(), new std::string("true"));
  if (node->stmt_else != nullptr)
    printStmt(node->stmt_else, node->idTag(), new std::string("false"));
  if (node->stmtListMain != nullptr)
    printStmtList(node->stmtListMain, node->idTag(), new std::string("true"));
  if (node->stmtListElse != nullptr)
    printStmtList(node->stmtListElse, node->idTag(), new std::string("false"));
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
  
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  switch (node->type)
  {
  case CaseDefaultType::case_stmt:
    GRAPH_STR += *node->idTag() + " [label=\"Case \"];\n";
    printExpr(node->expr, node->idTag(), new std::string("condition"));
    printStmtList(node->stmtList, node->idTag(), new std::string("code"));
    break;

  case CaseDefaultType::default_stmt:
    GRAPH_STR += *node->idTag() + " [label=\"Default \"];\n";
    printStmtList(node->stmtList, node->idTag(), new std::string("code"));
    break;

  case CaseDefaultType::finally_stmt:
    GRAPH_STR += *node->idTag() + " [label=\"Finally \"];\n";
    printStmtList(node->stmtList, node->idTag(), new std::string("code"));
    break;
  }
};

void printStmtList(StmtList *node, std::string *parentId, std::string *arrowLabel)
{
  GRAPH_STR += *node->idTag() + " [label=\"Stmt list\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "[label=\"" + *arrowLabel + "\"];\n";

  for (int i = 0; i < node->vector.size(); i++) {
      printStmt((node->vector)[i], node->idTag(), new std::string(""));
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
  GRAPH_STR += *node->idTag() + " [label=\"Static var\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  if (node->id != nullptr)
    printStringValueNode(node->id, node->idTag(), new std::string(""));
  if(node->expr != nullptr)
    printExpr(node->expr, node->idTag(), new std::string(""));
}

void printGlobalVarList(GlobalVarList *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"Global var list\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  for (int i = 0; i < node->vector.size(); i++) {
      printGlobalVar((node->vector)[i], node->idTag());
  }
};

void printGlobalVar(GlobalVarNode *node, std::string *parentId)
{
  GRAPH_STR += *node->idTag() + " [label=\"Global var\"];\n";
  GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

  if (node->id != nullptr)
    printStringValueNode(node->id, node->idTag(), new std::string(""));
  if(node->get_value != nullptr)
    printGetValue(node->get_value, node->idTag());
}

void printExpr(ExprNode *node, std::string *parentId, std::string *arrowLabel)
{
  // Значения
  switch (node->exprType)
  {
  case ExprType::int_val: //Если просто значение, может просто его и печатать? А то получится узел ради узла
    GRAPH_STR += *node->idTag() + " [label=\"" + std::to_string(node->int_val) + "\"];\n";
    break;

  case ExprType::string_val:
    GRAPH_STR += *node->idTag() + " [label=\" \\\"" + *node->string_val + "\\\" \"];\n";
    break;
  
  // Ключевые слова
  case ExprType::this_keyword:
    GRAPH_STR += *node->idTag() + " [label=\" This \"];\n";
    break;

  case ExprType::self_keyword:
    GRAPH_STR += *node->idTag() + " [label=\" Self \"];\n";
    break;

  case ExprType::parent_keyword:
    GRAPH_STR += *node->idTag() + " [label=\" Parent \"];\n";
    break;

  // Переменные
  case ExprType::variable:
    GRAPH_STR += *node->idTag() + " [label=\"Variable\"];\n";
    printGetValue(node->get_value, node->idTag());
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    break;

  case ExprType::constant:
    GRAPH_STR += *node->idTag() + " [label=\" \\\"" + *node->id + "\\\" \"];\n";
    break;

  // Присвоение
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

  // Cast
  case ExprType::int_cast: 
    GRAPH_STR += *node->idTag() + " [label=\"Int cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::float_cast: 
    GRAPH_STR += *node->idTag() + " [label=\"Float cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::string_cast: 
    GRAPH_STR += *node->idTag() + " [label=\"String cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::array_cast: 
    GRAPH_STR += *node->idTag() + " [label=\"Array cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::object_cast: 
    GRAPH_STR += *node->idTag() + " [label=\"Object cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::bool_cast: 
    GRAPH_STR += *node->idTag() + " [label=\"Bool cast\"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  // Обращение к полям и методам класса
  // Right arrow
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

  case ExprType::class_method_ref_op:
    GRAPH_STR += *node->idTag() + " [label=\"->\"];\n";
    if (node->get_value != nullptr)
      printGetValue(node->get_value, node->idTag());
    printExpr(node->left, node->idTag(), new std::string("left"));
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    printExprList(node->listParams, node->idTag());
    break;

  //Quarter dot
  case ExprType::class_inst_field_ref_dots_op:
    GRAPH_STR += *node->idTag() + " [label=\"::\"];\n";
    if (node->get_value != nullptr)
      printGetValue(node->get_value, node->idTag());
    printExpr(node->left, node->idTag(), new std::string(""));
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    break;

  case ExprType::class_inst_field_by_ref_dots_op:
    GRAPH_STR += *node->idTag() + " [label=\"::\"];\n";
    if (node->get_value != nullptr)
      printGetValue(node->get_value, node->idTag());
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::class_inst_method_by_ref_op:
    GRAPH_STR += *node->idTag() + " [label=\"::\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    printExprList(node->listParams, node->idTag());
    break;

  case ExprType::class_inst_get_value_method_by_ref_op:
    GRAPH_STR += *node->idTag() + " [label=\"::\"];\n";
    if (node->get_value != nullptr)
      printGetValue(node->get_value, node->idTag());
    printExpr(node->left, node->idTag(), new std::string("left"));
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    printExprList(node->listParams, node->idTag());
    break;
  
  //Математические операции
  case ExprType::plus_op:
    GRAPH_STR += *node->idTag() + " [label=\"+\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::minus_op:
    GRAPH_STR += *node->idTag() + " [label=\"-\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::mult_op:
    GRAPH_STR += *node->idTag() + " [label=\" * \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::div_op:
    GRAPH_STR += *node->idTag() + " [label=\" / \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::mod_op:
    GRAPH_STR += *node->idTag() + " [label=\" % \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::pow_op:
    GRAPH_STR += *node->idTag() + " [label=\" pow \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  //Конкатенация
  case ExprType::concat_op:
    GRAPH_STR += *node->idTag() + " [label=\" concatenation \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;
  
  //Логические операции
  case ExprType::bool_more:
    GRAPH_STR += *node->idTag() + " [label=\">\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bool_less:
    GRAPH_STR += *node->idTag() + " [label=\"<\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bool_or:
    GRAPH_STR += *node->idTag() + " [label=\"||\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bool_and:
    GRAPH_STR += *node->idTag() + " [label=\"&&\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;
  
  case ExprType::bool_equal:
    GRAPH_STR += *node->idTag() + " [label=\"==\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bool_equal_strict:
    GRAPH_STR += *node->idTag() + " [label=\"===\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bool_equal_more:
    GRAPH_STR += *node->idTag() + " [label=\" >= \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bool_equal_less:
    GRAPH_STR += *node->idTag() + " [label=\" <= \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bool_not:
    GRAPH_STR += *node->idTag() + " [label=\"!\"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    break;
  
  //Logic
  case ExprType::logic_and:
    GRAPH_STR += *node->idTag() + " [label=\" AND \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::logic_or:
    GRAPH_STR += *node->idTag() + " [label=\" OR \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::logic_xor:
    GRAPH_STR += *node->idTag() + " [label=\" XOR \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  //Bitwise
  case ExprType::bitwise_shift_l:
    GRAPH_STR += *node->idTag() + " [label=\" SHIFT_L \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bitwise_shift_r:
    GRAPH_STR += *node->idTag() + " [label=\" SHIFT_R \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bitwise_xor:
    GRAPH_STR += *node->idTag() + " [label=\" ^ \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bitwise_and:
    GRAPH_STR += *node->idTag() + " [label=\" & \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bitwise_or:
    GRAPH_STR += *node->idTag() + " [label=\" | \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::bitwise_not:
    GRAPH_STR += *node->idTag() + " [label=\" ~ \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  //Unary
  case ExprType::u_minus_op:
    GRAPH_STR += *node->idTag() + " [label=\" UNARY MINUS \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    break;
  
  case ExprType::u_plus_op:
    GRAPH_STR += *node->idTag() + " [label=\" UNARY PLUS \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    break;

  //Clone
  case ExprType::clone_op:
    GRAPH_STR += *node->idTag() + " [label=\" CLONE \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    break;
  
  //Trenary 
  case ExprType::ternary_op:
    GRAPH_STR += *node->idTag() + " [label=\" Trenary \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    if(node->central != nullptr)
      printExpr(node->central, node->idTag(), new std::string("central"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;
  
  //Ref op
  case ExprType::ref_op:
    GRAPH_STR += *node->idTag() + " [label=\" Trenary \"];\n";
    printGetValue(node->get_value, node->idTag());
    printExpr(node->right, node->idTag(), new std::string(""));
    break;

  //Array op
  case ExprType::get_value_array:
    GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  case ExprType::add_array_val:
    GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
    printExpr(node->left, node->idTag(), new std::string("left"));
    printExpr(node->right, node->idTag(), new std::string("right"));
    break;

  //Functions op
  case ExprType::call_get_value_func:
    GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    printExprList(node->listParams, node->idTag());
    break;

  //Declarations
  case ExprType::new_decl:
    GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    printExprList(node->listParams, node->idTag());
    break;

  case ExprType::new_decl_no_params:
    GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    break;
  
  case ExprType::new_decl_no_id:
    GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
    printExpr(node->left, node->idTag(), new std::string(""));
    break;

  case ExprType::new_get_value_decl:
    GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
    printGetValue(node->get_value, node->idTag());
    printStringValueNode(node->id, node->idTag(), new std::string(""));
    printExprList(node->listParams, node->idTag());
    break;
  
  case ExprType::new_get_value_decl_no_params:
    GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
    printGetValue(node->get_value, node->idTag());
    printStringValueNode(node->id, node->idTag(), new std::string(""));
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