#include "semantic.h"

vector<string *> sem_errors;
string *file_name;

//Global scope vars
vector<ExprNode *> variables;
//Global scope consts
vector<ConstDeclNode *> consts;
//Global scope functions
vector<FunctionStmtDeclNode *> functions;
//Global scope classes
vector<ClassStmtNode *> classes;
//Global scope interfaces
vector<InterfaceStmtDeclNode *> interfaces;
//Global scope traits
vector<TraitStmtDeclNode *> traits;

void inspectExpr(ExprNode *node, const vector<ExprNode *> &variablesScope, const vector<ConstDeclNode *> &constsScope,
                 const vector<FunctionStmtDeclNode *> &functionsScope, const vector<ClassStmtNode *> &classesScope,
                 bool isInClass = false);

void inspectFunction(FunctionStmtDeclNode *node);

void inspectStmt(StmtNode *node, const vector<ExprNode *> &variablesScope,
                 const vector<FunctionStmtDeclNode *> &functionsScope, const vector<ClassStmtNode *> &classesScope,
                 const vector<ConstDeclNode *> &constsScope, bool isInClass = false);

bool isDeclaredVariable(ExprNode *node, const vector<ExprNode *> &list) {
    if (node == nullptr || node->id == nullptr) return false;

    return any_of(list.cbegin(), list.cend(),
                  [&node](auto &var) { return *var->id == *node->id; });
}

bool isDeclaredConst(ConstDeclNode *node, const vector<ConstDeclNode *> &list) {
    if (node == nullptr || node->id == nullptr) return false;

    return any_of(list.cbegin(), list.cend(),
                  [&node](auto &var) { return *var->id == *node->id; });
}

bool isDeclaredFunction(FunctionStmtDeclNode *node, const vector<FunctionStmtDeclNode *> &list) {
    if (node == nullptr || node->function_def == nullptr) return false;

    return any_of(list.cbegin(), list.cend(),
                  [&node](auto &var) {
                      return *var->function_def->func_id == *node->function_def->func_id;
                  });
}

bool isDeclaredClass(ClassStmtDeclNode *node, const vector<ClassStmtDeclNode *> &list) {
    if (node == nullptr || node->class_def == nullptr) return false;

    return any_of(list.cbegin(), list.cend(),
                  [&node](auto &var) {
                      return *var->class_def->class_id == *node->class_def->class_id;
                  });
}

void inspectGlobalScope(StartNode *node) {
    if (node == nullptr || node->top_stmt_list == nullptr) return;

    for (auto *tmp: node->top_stmt_list->vector) {
        switch (tmp->type) {
            case TopStmtType::stmt_top_type:
                inspectStmt(tmp->stmt, variables, functions, classes,
                            consts);
                break;
            case TopStmtType::class_top_type:
                break;
            case TopStmtType::function_top_type:
                inspectFunction(tmp->func_stmt_decl);
                break;
            case TopStmtType::interface_top_type:
                break;
            case TopStmtType::trait_top_type:
                break;
        }
    }
}

void inspectStmt(StmtNode *node, vector<ExprNode *> &variablesScope, vector<FunctionStmtDeclNode *> &functionsScope,
                 vector<ClassStmtNode *> &classesScope, vector<ConstDeclNode *> &constsScope, bool isInClass) {
    if (node == nullptr) return;

    switch (node->type) {
        case StmtType::expr:
            inspectExpr(node->expr_left, variablesScope, constsScope, functionsScope, classesScope, isInClass);
            break;
        case StmtType::for_stmt:
            break;
        case StmtType::foreach_stmt:
            break;
        case StmtType::do_while_stmt:
            break;
        case StmtType::while_stmt:
            break;
    }
}

void inspectExpr(ExprNode *node, vector<ExprNode *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                 vector<FunctionStmtDeclNode *> &functionsScope, vector<ClassStmtNode *> &classesScope,
                 bool isInClass) {
    if (node == nullptr) return;

    switch (node->exprType) {
        case ExprType::assign_op:
            //if re-assign $this
            if (*node->left->id == "this" && node->get_value != nullptr && node->get_value->count == 1)
                //Throw fatal error
                throw runtime_error(string("Fatal error: Cannot re-assign $this in " + *file_name));
            //if use right-side variable is not declared
            if (node->right->exprType == ExprType::variable && !isDeclaredVariable(node->right, variablesScope)) {
                sem_errors.push_back(
                        new string("Warning: Undefined variable $" + *node->right->id + " in " + *file_name));
                node->right = ExprNode::CreateFromAssignOp(node->right, ExprNode::CreateFromNull());
                variablesScope.push_back(node->right->left);
            }

            inspectExpr(node->left, variablesScope, constsScope, functionsScope, classesScope, isInClass);
            inspectExpr(node->right, variablesScope, constsScope, functionsScope, classesScope, isInClass);
            break;
        case ExprType::assign_ref_op:
            break;
        case ExprType::class_field_by_ref_op:
            //TODO добавить еще подобных кейз случаев
            break;
        case ExprType::this_keyword:
            if (!isInClass)
                sem_errors.push_back(new string(
                        "Fatal error: Uncaught error: Using $this when in not in object context in " + *file_name));
            break;
    }
}
