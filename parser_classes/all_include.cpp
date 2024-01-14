#include <iostream>
#include "all_include.hpp"

StartNode *startNode;

string GRAPH_STR("digraph Tree {\n");

static int VALUE_ID = 0; // Для тегов узлов с конечным значением

void printTopStmtList(TopStmtList *node, string *parentId);

void printTopStmt(TopStmtNode *node, string *parentId);

void printStmt(StmtNode *node, string *parentId, string *arrowLabel);

void printIfStmt(IfStmtNode *node, string *parentId);

void printSwitchStmt(SwitchStmtNode *node, string *parentId);

void printCaseDefaultStmtList(CaseDefaultStmtList *node, string *parentId);

void printCaseDefaultStmt(CaseDefaultStmtNode *node, string *parentId);

void printStmtList(StmtList *node, string *parentId, string *arrowLabel);

void printStaticVarList(StaticVarList *node, string *parentId);

void printStaticVar(StaticVarNode *node, string *parentId);

void printGlobalVarList(GlobalVarList *node, string *parentId);

void printGlobalVar(GlobalVarNode *node, string *parentId);

void printWhileStmt(WhileStmtNode *node, string *parentId);

void printDoWhileStmt(DoWhileStmtNode *node, string *parentId);

void printForStmt(ForStmtNode *node, string *parentId);

void printForEachStmt(ForEachStmtNode *node, string *parentId);

void printMatchStmt(MatchStmtNode *node, string *parentId);

void printMatchArmList(MatchArmList *node, string *parentId);

void printMatchArm(MatchArmNode *node, string *parentId);

void printConstDeclList(ConstDeclList *node, string *parentId);

void printConstDecl(ConstDeclNode *node, string *parentId);

void printHtmlStmt(HtmlStmtNode *node, string *parentId);

void printExpr(ExprNode *node, string *parentId, string *arrowLabel);

void printExprList(ExprList *node, string *parentId);

void printFunctionStmtDecl(FunctionStmtDeclNode *node, string *parentId);

void printFunctionDef(FunctionDefNode *node, string *parentId);

void printExprFuncList(ExprFuncList *node, string *parentId);

void printExprFunc(ExprFuncNode *node, string *parentId);

void printGetValueFunc(GetValueFuncNode *node, string *parentId);

void printClassStmtDecl(ClassStmtDeclNode *node, string *parentId);

void printClassDef(ClassDefNode *node, string *parentId);

void printClassStmtList(ClassStmtList *node, string *parentId);

void printClassStmt(ClassStmtNode *node, string *parentId);

void printClassExpr(ClassExprNode *node, string *parentId);

void printClassAccessModList(ClassAccessModList *node, string *parentId);

void printClassAccessMod(ClassAccessModNode *node, string *parentId);

void printInterfaceStmtDecl(InterfaceStmtDeclNode *node, string *parentId);

void printInterfaceExprDef(InterfaceExprDefNode *node, string *parentId);

void printInterfaceStmtList(InterfaceStmtList *node, string *parentId);

void printInterfaceStmt(InterfaceStmtNode *node, string *parentId);

void printTraitStmtDeclNode(TraitStmtDeclNode *node, string *parentId);

void printGetValue(GetValueNode *node, string *parentId);

void printIdList(IdListNode *node, string *parentId, string *arrowLabel);

void printStringValueNode(string *value, string *parentId,
                          string *arrowLabel); // Печатает узел со строковым значением

void printTreeGraph(StartNode *node) {
    cout << "START PRINT\n";
    GRAPH_STR += *node->idTag() + " [label=\"Start\"];\n";

    if (node->html_before != nullptr)
        printHtmlStmt(node->html_before, node->idTag());
    if (node->top_stmt_list != nullptr)
        printTopStmtList(node->top_stmt_list, node->idTag());
    if (node->html_after != nullptr)
        printHtmlStmt(node->html_after, node->idTag());
}

void printTopStmtList(TopStmtList *node, string *parentId) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Top stmt list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printTopStmt((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printTopStmt(TopStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Top stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->stmt != nullptr)
        printStmt(node->stmt, node->idTag(), new string(""));
    if (node->func_stmt_decl != nullptr)
        printFunctionStmtDecl(node->func_stmt_decl, node->idTag());
    if (node->class_stmt_decl != nullptr)
        printClassStmtDecl(node->class_stmt_decl, node->idTag());
    if (node->interface_stmt_decl != nullptr)
        printInterfaceStmtDecl(node->interface_stmt_decl, node->idTag());
    if (node->trait_stmt_decl != nullptr)
        printTraitStmtDeclNode(node->trait_stmt_decl, node->idTag());
    delete parentId;
}

//Возможно переделать
void printStmt(StmtNode *node, string *parentId, string *arrowLabel) {
    cout << "PRINT STMT\n";
    switch (node->type) {
        case StmtType::throw_stmt:
            GRAPH_STR += *node->idTag() + " [label=\"Throw\"];\n";
            printExpr(node->expr_left, node->idTag(), new string(""));
            break;

        case StmtType::return_stmt:
            GRAPH_STR += *node->idTag() + " [label=\"Return\"];\n";
            printExpr(node->expr_left, node->idTag(), new string(""));
            break;

        case StmtType::break_stmt:
            GRAPH_STR += *node->idTag() + " [label=\"Break\"];\n";
            break;

        case StmtType::t_echo_stmt:
            cout << GRAPH_STR.size() << " from echo_stmt" << "\n";
            GRAPH_STR += *node->idTag() + " [label=\"t-echo\"];\n";
            printExpr(node->expr_left, node->idTag(), new string(""));
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
            if (node->stmtList != nullptr)
                printStmtList(node->stmtList, node->idTag(), new string(""));
            if (node->expr_left != nullptr)
                printExpr(node->expr_left, node->idTag(), new string(
                        "left"));
            if (node->expr_right != nullptr)
                printExpr(node->expr_right, node->idTag(), new string(
                        "right"));
            if (node->static_var != nullptr)
                printStaticVarList(node->static_var, node->idTag());
            if (node->global_var != nullptr)
                printGlobalVarList(node->global_var, node->idTag());
            if (node->while_stmt != nullptr)
                printWhileStmt(node->while_stmt, node->idTag());
            if (node->do_while_stmt != nullptr)
                printDoWhileStmt(node->do_while_stmt, node->idTag());
            if (node->for_stmt != nullptr)
                printForStmt(node->for_stmt, node->idTag());
            if (node->foreach_stmt != nullptr)
                printForEachStmt(node->foreach_stmt, node->idTag());
            if (node->match_stmt != nullptr)
                printMatchStmt(node->match_stmt, node->idTag());
            if (node->const_decl != nullptr)
                printConstDeclList(node->const_decl, node->idTag());
            if (node->html_stmt != nullptr)
                printHtmlStmt(node->html_stmt, node->idTag());
            break;
    }

    GRAPH_STR += *node->idTag() + " -> " + *parentId + "[label=\"" + *arrowLabel + "\"];\n";
    delete parentId;
    delete arrowLabel;
};

void printIfStmt(IfStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"If stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string("condition"));
    if (node->stmt_main != nullptr)
        printStmt(node->stmt_main, node->idTag(), new string("true"));
    if (node->stmt_else != nullptr)
        printStmt(node->stmt_else, node->idTag(), new string("false"));
    if (node->stmtListMain != nullptr)
        printStmtList(node->stmtListMain, node->idTag(), new string("true"));
    if (node->stmtListElse != nullptr)
        printStmtList(node->stmtListElse, node->idTag(), new string("false"));
    delete parentId;
};

void printSwitchStmt(SwitchStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Switch stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string("param"));
    if (node->defaultStmtList != nullptr)
        printCaseDefaultStmtList(node->defaultStmtList, node->idTag());
    delete parentId;
}

void printCaseDefaultStmtList(CaseDefaultStmtList *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Case default stmt list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printCaseDefaultStmt((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printCaseDefaultStmt(CaseDefaultStmtNode *node, string *parentId) {

    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    switch (node->type) {
        case CaseDefaultType::case_stmt:
            GRAPH_STR += *node->idTag() + " [label=\"Case \"];\n";
            printExpr(node->expr, node->idTag(), new string("condition"));
            printStmtList(node->stmtList, node->idTag(), new string("code"));
            break;

        case CaseDefaultType::default_stmt:
            GRAPH_STR += *node->idTag() + " [label=\"Default \"];\n";
            printStmtList(node->stmtList, node->idTag(), new string("code"));
            break;

        case CaseDefaultType::finally_stmt:
            GRAPH_STR += *node->idTag() + " [label=\"Finally \"];\n";
            printStmtList(node->stmtList, node->idTag(), new string("code"));
            break;
    }
    delete parentId;
}

void printStmtList(StmtList *node, string *parentId, string *arrowLabel) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Stmt list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "[label=\"" + *arrowLabel + "\"];\n";

    for (int i = 0; i < node->vector.size(); i++) {
        cout << GRAPH_STR.size() << " from Stmt list member #" << i << "\n";
        printStmt((node->vector)[i], node->idTag(), new string(""));
    }
    delete parentId;
    delete arrowLabel;
}

void printStaticVarList(StaticVarList *node, string *parentId) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Static var list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printStaticVar((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printStaticVar(StaticVarNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Static var\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->id != nullptr)
        printStringValueNode(node->id, node->idTag(), new string(""));
    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string(""));
    delete parentId;
}

void printGlobalVarList(GlobalVarList *node, string *parentId) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Global var list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printGlobalVar((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printGlobalVar(GlobalVarNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Global var\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->id != nullptr)
        printStringValueNode(node->id, node->idTag(), new string(""));
    if (node->get_value != nullptr)
        printGetValue(node->get_value, node->idTag());
    delete parentId;
}

void printWhileStmt(WhileStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"While stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string("condition"));
    if (node->stmt != nullptr)
        printStmt(node->stmt, node->idTag(), new string("body"));
    if (node->stmtList != nullptr)
        printStmtList(node->stmtList, node->idTag(), new string("body"));
    delete parentId;
}

void printDoWhileStmt(DoWhileStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Do while stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string("condition"));
    if (node->stmt != nullptr)
        printStmt(node->stmt, node->idTag(), new string("body"));
    delete parentId;
}

void printForStmt(ForStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Do while stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->expr_left != nullptr)
        printExpr(node->expr_left, node->idTag(), new string("condition left"));
    if (node->expr_central != nullptr)
        printExpr(node->expr_central, node->idTag(), new string("condition central"));
    if (node->expr_right != nullptr)
        printExpr(node->expr_right, node->idTag(), new string("condition right"));
    if (node->stmt != nullptr)
        printStmt(node->stmt, node->idTag(), new string("body"));
    if (node->stmtList)
        printStmtList(node->stmtList, node->idTag(), new string("body"));
    delete parentId;
}

void printForEachStmt(ForEachStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Do while stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->expr_left != nullptr)
        printExpr(node->expr_left, node->idTag(), new string("condition left"));
    if (node->expr_right != nullptr)
        printExpr(node->expr_right, node->idTag(), new string("condition right"));
    if (node->stmt != nullptr)
        printStmt(node->stmt, node->idTag(), new string("body"));
    if (node->id != nullptr)
        printStringValueNode(node->id, node->idTag(), new string("param name"));
    if (node->stmtList)
        printStmtList(node->stmtList, node->idTag(), new string("body"));
    delete parentId;
}

void printMatchStmt(MatchStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Match stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string("condition"));
    if (node->matchList != nullptr)
        printMatchArmList(node->matchList, node->idTag());
    delete parentId;
}

void printMatchArmList(MatchArmList *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Match arm list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printMatchArm((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printMatchArm(MatchArmNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Match arm\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->exprList != nullptr)
        printExprList(node->exprList, node->idTag());
    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string("default"));
    delete parentId;
}

void printConstDeclList(ConstDeclList *node, string *parentId) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Const declaration list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printConstDecl((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printConstDecl(ConstDeclNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Const declaration\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->id != nullptr)
        printStringValueNode(node->id, node->idTag(), new string(""));
    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string(""));
    delete parentId;
}

void printHtmlStmt(HtmlStmtNode *node, string *parentId) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Html stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
    delete parentId;
}

//ExprNode
void printExpr(ExprNode *node, string *parentId, string *arrowLabel) {
    cout << "PRINT EXPR\n";
    cout << GRAPH_STR.size() << " of " << GRAPH_STR.max_size() << "\n";
    // Значения
    switch (node->exprType) {
        case ExprType::int_val: //Если просто значение, может просто его и печатать? А то получится узел ради узла
            cout << GRAPH_STR.size() << " from int_val" << "\n";
            GRAPH_STR += *node->idTag() + " [label=\"" + to_string(node->int_val) + "\"];\n";
            cout << GRAPH_STR.size() << " from int_val #2" << "\n";
            break;
        case ExprType::string_val:
            cout << GRAPH_STR.size() << " from string_val" << "\n";
            GRAPH_STR += *node->idTag() + " [label=\" \\\"" + *node->string_val + "\\\" \"];\n";
            break;
            // Ключевые слова
        case ExprType::this_keyword:
            cout << GRAPH_STR.size() << " from this key\n";
            GRAPH_STR += *node->idTag() + " [label=\" This \"];\n";
            break;
        case ExprType::self_keyword:
            cout << GRAPH_STR.size() << " from self key\n";
            GRAPH_STR += *node->idTag() + " [label=\" Self \"];\n";
            break;
        case ExprType::parent_keyword:
            GRAPH_STR += *node->idTag() + " [label=\" Parent \"];\n";
            break;
            // Переменные
        case ExprType::variable:
            cout << GRAPH_STR.size() << " from variable" << "\n";
            GRAPH_STR += *node->idTag() + " [label=\"Variable\"];\n";
            printGetValue(node->get_value, node->idTag());
            printStringValueNode(node->id, node->idTag(), new string(""));
            break;
        case ExprType::id_type:
            cout << GRAPH_STR.size() << " from constant" << "\n";
            GRAPH_STR += *node->idTag() + " [label=\"" + *node->id + "\"];\n";
            break;
            // Присвоение
        case ExprType::assign_op:
            GRAPH_STR += *node->idTag() + " [label=\"=\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::assign_ref_op:
            GRAPH_STR += *node->idTag() + " [label=\"assign ref\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
            // Cast
        case ExprType::int_cast:
            cout << GRAPH_STR.size() << " from int cast\n";
            GRAPH_STR += *node->idTag() + " [label=\"Int cast\"];\n";
            printExpr(node->left, node->idTag(), new string(""));
            break;
        case ExprType::float_cast:
            cout << GRAPH_STR.size() << " from float cast\n";
            GRAPH_STR += *node->idTag() + " [label=\"Float cast\"];\n";
            printExpr(node->left, node->idTag(), new string(""));
            break;
        case ExprType::string_cast:
            cout << GRAPH_STR.size() << " from string cast\n";
            GRAPH_STR += *node->idTag() + " [label=\"String cast\"];\n";
            printExpr(node->left, node->idTag(), new string(""));
            break;
        case ExprType::array_cast:
            cout << GRAPH_STR.size() << " from array cast\n";
            GRAPH_STR += *node->idTag() + " [label=\"Array cast\"];\n";
            printExpr(node->left, node->idTag(), new string(""));
            break;
        case ExprType::object_cast:
            cout << GRAPH_STR.size() << " from object cast\n";
            GRAPH_STR += *node->idTag() + " [label=\"Object cast\"];\n";
            printExpr(node->left, node->idTag(), new string(""));
            break;
        case ExprType::bool_cast:
            GRAPH_STR += *node->idTag() + " [label=\"Bool cast\"];\n";
            printExpr(node->left, node->idTag(), new string(""));
            break;
            // Обращение к полям и методам класса
            // Right arrow
        case ExprType::class_inst_field_ref_op:
            GRAPH_STR += *node->idTag() + " [label=\"->\"];\n";
            if (node->get_value != nullptr)
                printGetValue(node->get_value, node->idTag());
            printExpr(node->left, node->idTag(), new string(""));
            printStringValueNode(node->id, node->idTag(), new string(""));
            break;
        case ExprType::class_inst_field_by_ref_op:
            GRAPH_STR += *node->idTag() + " [label=\"->\"];\n";
            if (node->get_value != nullptr)
                printGetValue(node->get_value, node->idTag());
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::class_method_ref_op:
            GRAPH_STR += *node->idTag() + " [label=\"->\"];\n";
            if (node->get_value != nullptr)
                printGetValue(node->get_value, node->idTag());
            printExpr(node->left, node->idTag(), new string("left"));
            printStringValueNode(node->id, node->idTag(), new string(""));
            if (node->listParams != nullptr)
                printExprList(node->listParams, node->idTag());
            break;
            //Quarter dot
        case ExprType::class_inst_field_ref_dots_op:
            GRAPH_STR += *node->idTag() + " [label=\"::\"];\n";
            if (node->get_value != nullptr)
                printGetValue(node->get_value, node->idTag());
            printExpr(node->left, node->idTag(), new string(""));
            printStringValueNode(node->id, node->idTag(), new string(""));
            break;
        case ExprType::class_inst_field_by_ref_dots_op:
            GRAPH_STR += *node->idTag() + " [label=\"::\"];\n";
            if (node->get_value != nullptr)
                printGetValue(node->get_value, node->idTag());
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::class_inst_method_by_ref_op_dots:
            GRAPH_STR += *node->idTag() + " [label=\"::\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printStringValueNode(node->id, node->idTag(), new string("right"));
            if (node->listParams != nullptr)
                printExprList(node->listParams, node->idTag());
            break;
        case ExprType::class_inst_get_value_method_by_ref_op_dots:
            GRAPH_STR += *node->idTag() + " [label=\"::\"];\n";
            if (node->get_value != nullptr)
                printGetValue(node->get_value, node->idTag());
            printExpr(node->left, node->idTag(), new string("left"));
            printStringValueNode(node->id, node->idTag(), new string(""));
            if (node->listParams != nullptr)
                printExprList(node->listParams, node->idTag());
            break;
            //Математические операции
        case ExprType::plus_op:
            GRAPH_STR += *node->idTag() + " [label=\"+\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::minus_op:
            GRAPH_STR += *node->idTag() + " [label=\"-\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::mult_op:
            GRAPH_STR += *node->idTag() + " [label=\" * \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::div_op:
            GRAPH_STR += *node->idTag() + " [label=\" / \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::mod_op:
            GRAPH_STR += *node->idTag() + " [label=\" % \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::pow_op:
            GRAPH_STR += *node->idTag() + " [label=\" pow \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
            //Конкатенация
        case ExprType::concat_op:
            GRAPH_STR += *node->idTag() + " [label=\" concatenation \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
            //Логические операции
        case ExprType::bool_more:
            GRAPH_STR += *node->idTag() + " [label=\">\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bool_less:
            GRAPH_STR += *node->idTag() + " [label=\"<\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bool_or:
            GRAPH_STR += *node->idTag() + " [label=\"||\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bool_and:
            GRAPH_STR += *node->idTag() + " [label=\"&&\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bool_equal:
            GRAPH_STR += *node->idTag() + " [label=\"==\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bool_equal_strict:
            GRAPH_STR += *node->idTag() + " [label=\"===\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bool_equal_more:
            GRAPH_STR += *node->idTag() + " [label=\" >= \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bool_equal_less:
            GRAPH_STR += *node->idTag() + " [label=\" <= \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bool_not:
            GRAPH_STR += *node->idTag() + " [label=\"!\"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            break;
            //Logic
        case ExprType::logic_and:
            GRAPH_STR += *node->idTag() + " [label=\" AND \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::logic_or:
            GRAPH_STR += *node->idTag() + " [label=\" OR \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::logic_xor:
            GRAPH_STR += *node->idTag() + " [label=\" XOR \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
            //Bitwise
        case ExprType::bitwise_shift_l:
            GRAPH_STR += *node->idTag() + " [label=\" SHIFT_L \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bitwise_shift_r:
            GRAPH_STR += *node->idTag() + " [label=\" SHIFT_R \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bitwise_xor:
            GRAPH_STR += *node->idTag() + " [label=\" ^ \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bitwise_and:
            GRAPH_STR += *node->idTag() + " [label=\" & \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bitwise_or:
            GRAPH_STR += *node->idTag() + " [label=\" | \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::bitwise_not:
            GRAPH_STR += *node->idTag() + " [label=\" ~ \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
            //Unary
        case ExprType::u_minus_op:
            GRAPH_STR += *node->idTag() + " [label=\" UNARY MINUS \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            break;
        case ExprType::u_plus_op:
            GRAPH_STR += *node->idTag() + " [label=\" UNARY PLUS \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            break;
            //Clone
        case ExprType::clone_op:
            GRAPH_STR += *node->idTag() + " [label=\" CLONE \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            break;
            //Trenary
        case ExprType::ternary_op:
            GRAPH_STR += *node->idTag() + " [label=\" Trenary \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            if (node->central != nullptr)
                printExpr(node->central, node->idTag(), new string("central"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
            //Ref op
        case ExprType::ref_op:
            GRAPH_STR += *node->idTag() + " [label=\" Trenary \"];\n";
            printGetValue(node->get_value, node->idTag());
            printExpr(node->right, node->idTag(), new string(""));
            break;
            //Array op
        case ExprType::get_array_val:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
        case ExprType::add_array_val:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printExpr(node->left, node->idTag(), new string("left"));
            printExpr(node->right, node->idTag(), new string("right"));
            break;
            //Functions op
        case ExprType::call_get_value_func:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printStringValueNode(node->id, node->idTag(), new string(""));
            if (node->listParams != nullptr)
                printExprList(node->listParams, node->idTag());
            break;
            //Declarations
        case ExprType::new_decl:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printStringValueNode(node->id, node->idTag(), new string(""));
            if (node->listParams != nullptr)
                printExprList(node->listParams, node->idTag());
            break;
        case ExprType::new_decl_no_params:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printStringValueNode(node->id, node->idTag(), new string(""));
            break;
        case ExprType::new_decl_no_id:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printExpr(node->left, node->idTag(), new string(""));
            break;
        case ExprType::new_get_value_decl:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printGetValue(node->get_value, node->idTag());
            printStringValueNode(node->id, node->idTag(), new string(""));
            if (node->listParams != nullptr)
                printExprList(node->listParams, node->idTag());
            break;
        case ExprType::new_get_value_decl_no_params:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printGetValue(node->get_value, node->idTag());
            printStringValueNode(node->id, node->idTag(), new string(""));
            break;
            //TODO воэ это все ниже
        case ExprType::instance_of:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printExpr(node->left, node->idTag(), new string("variable"));
            printExpr(node->right, node->idTag(), new string("object type"));
            break;
        case float_val:
            cout << GRAPH_STR.size() << " from float_val" << "\n";
            GRAPH_STR += *node->idTag() + " [label=\"" + to_string(node->float_val) + "\"];\n";
            break;
        case command_string_val:
            break;
        case class_field_ref_op:
            break;
        case class_field_by_ref_op:
            break;
        case class_method_by_ref_op:
            cout << "USELESS RULE";
            break;
        case call_func:
            GRAPH_STR += *node->idTag() + " [label=\" Expr \"];\n";
            printStringValueNode(node->id, node->idTag(), new string("id"));
            printExprList(node->listParams, node->idTag());
            break;
    }
    cout << GRAPH_STR.size() << "\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "[label=\"" + *arrowLabel + "\"];\n";
    delete parentId;
    delete arrowLabel;
}

void printExprList(ExprList *node, string *parentId) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Expr list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        cout << GRAPH_STR.size() << " from expr list #" << i << "\n";
        printExpr(node->vector[i], node->idTag(), new string("part"));
    }
    delete parentId;
}

//Function stmt
void printFunctionStmtDecl(FunctionStmtDeclNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Function stmt declaration\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
    cout << GRAPH_STR.size() << " from function declaration\n";

    if (node->function_def != nullptr)
        printFunctionDef(node->function_def, node->idTag());
    if (node->stmt_list != nullptr)
        printStmtList(node->stmt_list, node->idTag(), new string("body"));
    delete parentId;
}

void printFunctionDef(FunctionDefNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Function definition\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->func_id != nullptr)
        printStringValueNode(node->func_id, node->idTag(), new string("function name"));
    if (node->type_id != nullptr)
        printStringValueNode(node->type_id, node->idTag(), new string("function type"));
    if (node->expr_func_list != nullptr)
        printExprFuncList(node->expr_func_list, node->idTag());
    delete parentId;
}

void printExprFuncList(ExprFuncList *node, string *parentId) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Expr function list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + " [label=\"params\"];\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printExprFunc((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printExprFunc(ExprFuncNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Expr function\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->get_value_func != nullptr)
        printGetValueFunc(node->get_value_func, node->idTag());
    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string(""));
    delete parentId;
}

void printGetValueFunc(GetValueFuncNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Get value function\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
    cout << GRAPH_STR.size() << " from get value func\n";

    if (node->id_value != nullptr)
        printStringValueNode(node->id_value, node->idTag(), new string("name"));
    if (node->id_type != nullptr)
        printStringValueNode(node->id_type, node->idTag(), new string("type"));
    delete parentId;
}

//Class nodes
void printClassStmtDecl(ClassStmtDeclNode *node, string *parentId) {
    switch (node->type) {
        case ClassStmtDeclType::no_modifiers_type:
            GRAPH_STR += *node->idTag() + " [label=\"Class declaration\"];\n";
            break;

        case ClassStmtDeclType::abstract_type:
            GRAPH_STR += *node->idTag() + " [label=\"Class declaration abstract\"];\n";
            break;

        case ClassStmtDeclType::final_type:
            GRAPH_STR += *node->idTag() + " [label=\"Class declaration final\"];\n";
            break;
    }

    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->class_def != nullptr)
        printClassDef(node->class_def, node->idTag());
    if (node->class_stmt_list != nullptr)
        printClassStmtList(node->class_stmt_list, node->idTag());
    delete parentId;
}

void printClassDef(ClassDefNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Class definition\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->class_id != nullptr)
        printStringValueNode(node->class_id, node->idTag(), new string("name"));
    if (node->extend_id)
        printStringValueNode(node->extend_id, node->idTag(), new string("extends"));
    if (node->impl_id_list)
        printIdList(node->impl_id_list, node->idTag(), new string("implements"));
    delete parentId;
}

void printClassStmtList(ClassStmtList *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Class stmt list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        cout << GRAPH_STR.size() << " from class stmt list member #" << i << "\n";
        printClassStmt((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printClassStmt(ClassStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Class stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->class_expr != nullptr)
        printClassExpr(node->class_expr, node->idTag());
    if (node->access_mod != nullptr)
        printClassAccessModList(node->access_mod, node->idTag());
    if (node->function_stmt_decl != nullptr)
        printFunctionStmtDecl(node->function_stmt_decl, node->idTag());
    if (node->function_def != nullptr)
        printFunctionDef(node->function_def, node->idTag());
    if (node->id_list != nullptr)
        printIdList(node->id_list, node->idTag(), new string(""));
    if (node->class_stmt_decl != nullptr)
        printClassStmtDecl(node->class_stmt_decl, node->idTag());
    delete parentId;
}

void printClassExpr(ClassExprNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Class expr\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
    cout << GRAPH_STR.size() << " from class expr\n";

    if (node->access_mod_list != nullptr)
        printClassAccessModList(node->access_mod_list, node->idTag());
    if (node->get_value != nullptr)
        printGetValue(node->get_value, node->idTag());
    if (node->id != nullptr)
        printStringValueNode(node->id, node->idTag(), new string(""));
    if (node->expr != nullptr)
        printExpr(node->expr, node->idTag(), new string(""));
    if (node->const_decl_list != nullptr)
        printConstDeclList(node->const_decl_list, node->idTag());
    delete parentId;
}

void printClassAccessModList(ClassAccessModList *node, string *parentId) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Access mod list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printClassAccessMod((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printClassAccessMod(ClassAccessModNode *node, string *parentId) {
    cout << GRAPH_STR.size() << " from class access mode\n";
    switch (node->access_mod) {
        case ClassAccessMod::public_node:
            GRAPH_STR += *node->idTag() + " [label=\"Access mod: public\"];\n";
            break;

        case ClassAccessMod::protected_node:
            GRAPH_STR += *node->idTag() + " [label=\"Access mod: protected\"];\n";
            break;

        case ClassAccessMod::private_node:
            GRAPH_STR += *node->idTag() + " [label=\"Access mod: private\"];\n";
            break;

        case ClassAccessMod::final_node:
            GRAPH_STR += *node->idTag() + " [label=\"Access mod: final\"];\n";
            break;

        case ClassAccessMod::abstract_node:
            GRAPH_STR += *node->idTag() + " [label=\"Access mod: abstract\"];\n";
            break;

        case ClassAccessMod::read_only_node:
            GRAPH_STR += *node->idTag() + " [label=\"Access mod: read only\"];\n";
            break;

        case ClassAccessMod::static_node:
            GRAPH_STR += *node->idTag() + " [label=\"Access mod: static\"];\n";
            break;
    }
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
    delete parentId;
}

//Interface nodes
void printInterfaceStmtDecl(InterfaceStmtDeclNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Interface stmt declaration\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
    cout << GRAPH_STR.size() << " from interface decl\n";

    if (node->expr_definition != nullptr)
        printInterfaceExprDef(node->expr_definition, node->idTag());
    if (node->stmt_list != nullptr)
        printInterfaceStmtList(node->stmt_list, node->idTag());
    delete parentId;
}

void printInterfaceExprDef(InterfaceExprDefNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Interface expr definition\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->id != nullptr)
        printStringValueNode(node->id, node->idTag(), new string("name"));
    if (node->id_extended_list != nullptr)
        printIdList(node->id_extended_list, node->idTag(), new string("extends"));
    delete parentId;
}

void printInterfaceStmtList(InterfaceStmtList *node, string *parentId) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Interface stmt list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printInterfaceStmt((node->vector)[i], node->idTag());
    }
    delete parentId;
}

void printInterfaceStmt(InterfaceStmtNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Interface stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->access_mod != nullptr)
        printClassAccessModList(node->access_mod, node->idTag());
    if (node->function_def != nullptr)
        printFunctionDef(node->function_def, node->idTag());
    delete parentId;
}

void printTraitStmtDeclNode(TraitStmtDeclNode *node, string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Trait stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->id != nullptr)
        printStringValueNode(node->id, node->idTag(), new string(""));
    if (node->stmt_list != nullptr)
        printClassStmtList(node->stmt_list, node->idTag());
    delete parentId;
}

void printGetValue(GetValueNode *node, string *parentId) {
    cout << GRAPH_STR.size() << " from get value\n";
    GRAPH_STR += *node->idTag() + " [label=\"Get value count:" + to_string(node->count) + "\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";
    delete parentId;
}

void printIdList(IdListNode *node, string *parentId, string *arrowLabel) {
    if (node == nullptr)
        return;
    GRAPH_STR += *node->idTag() + " [label=\"Id list\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + " [label=\"" + *arrowLabel + "\"];\n";

    for (int i = 0; i < node->vector.size(); i++) {
        printStringValueNode((node->vector)[i], node->idTag(), new string(""));
    }
    delete parentId;
    delete arrowLabel;
}

void printStringValueNode(string *value, string *parentId, string *arrowLabel) {
    string tag("VAL_" + to_string(VALUE_ID++));

    cout << GRAPH_STR.size() << " from string value" << "\n";
    GRAPH_STR += tag + " [label=\"" + *value + "\"];\n";
    GRAPH_STR += tag + " -> " + *parentId + " [label=\"" + *arrowLabel + "\"];\n";
    delete value;
    delete parentId;
    delete arrowLabel;
}