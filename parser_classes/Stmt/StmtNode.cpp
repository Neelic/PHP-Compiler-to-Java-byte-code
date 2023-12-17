#include "StmtNode.hpp"

int StmtNode::GLOBAL_ID = 0;

StmtNode *StmtNode::CreateFromExpr(ExprNode *expr) {
    auto *tmp = new StmtNode();
    tmp->expr_left = expr;
    tmp->type = StmtType::expr;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromIfStmt(IfStmtNode *if_stmt) {
    auto *tmp = new StmtNode();
    tmp->if_stmt = if_stmt;
    tmp->type = StmtType::if_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromSwitchStmt(SwitchStmtNode *switch_stmt) {
    StmtNode *tmp = new StmtNode();
    tmp->switch_stmt = switch_stmt;
    tmp->type = StmtType::switch_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromStmtList(StmtList *stmtList) {
    StmtNode *tmp = new StmtNode();
    tmp->stmtList = stmtList;
    tmp->type = StmtType::stmt_list;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromStaticVar(StaticVarList *static_var) {
    StmtNode *tmp = new StmtNode();
    tmp->static_var = static_var;
    tmp->type = StmtType::static_var;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromGlobalVar(GlobalVarList *global_var) {
    StmtNode *tmp = new StmtNode();
    tmp->global_var = global_var;
    tmp->type = StmtType::global_var;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromWhileStmt(WhileStmtNode *while_stmt) {
    StmtNode *tmp = new StmtNode();
    tmp->while_stmt = while_stmt;
    tmp->type = StmtType::while_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromDoWhileStmt(DoWhileStmtNode *do_while_stmt) {
    StmtNode *tmp = new StmtNode();
    tmp->do_while_stmt = do_while_stmt;
    tmp->type = StmtType::do_while_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromForStmt(ForStmtNode *for_stmt) {
    auto *tmp = new StmtNode();
    tmp->for_stmt = for_stmt;
    tmp->type = StmtType::for_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromForEachStmt(ForEachStmtNode *foreach_stmt) {
    auto *tmp = new StmtNode();
    tmp->foreach_stmt = foreach_stmt;
    tmp->type = StmtType::foreach_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromThrowStmt(ExprNode *expr) {
    auto *tmp = new StmtNode();
    tmp->expr_left = expr;
    tmp->type = StmtType::throw_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromTryCatchStmt(TryCatchStmtNode *try_catch_stmt) {
    auto *tmp = new StmtNode();
    tmp->try_catch_stmt = try_catch_stmt;
    tmp->type = StmtType::try_catch_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromMatchStmt(MatchStmtNode *match_stmt) {
    auto *tmp = new StmtNode();
    tmp->match_stmt = match_stmt;
    tmp->type = StmtType::match_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromConstDecl(ConstDeclList *const_decl) {
    auto *tmp = new StmtNode();
    tmp->const_decl = const_decl;
    tmp->type = StmtType::const_decl;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromReturnStmt(ExprNode *expr_left) {
    auto *tmp = new StmtNode();
    tmp->expr_left = expr_left;
    tmp->type = StmtType::return_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromYieldStmt(ExprNode *expr_left) {
    auto *tmp = new StmtNode();
    tmp->expr_left = expr_left;
    tmp->type = StmtType::yield_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromYieldDoubleArrowStmt(ExprNode *expr_left, ExprNode *expr_right) {
    auto *tmp = new StmtNode();
    tmp->expr_left = expr_left;
    tmp->expr_right = expr_right;
    tmp->type = StmtType::yield_r_arrow_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromHtmlStmt(HtmlStmtNode *html_stmt) {
    auto *tmp = new StmtNode();
    tmp->html_stmt = html_stmt;
    tmp->type = StmtType::html_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromBreakStmt() {
    auto *tmp = new StmtNode();
    tmp->type = StmtType::break_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromTEchoStmt(ExprNode *expr_left) {
    auto *tmp = new StmtNode();
    tmp->expr_left = expr_left;
    tmp->type = StmtType::t_echo_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

StmtNode *StmtNode::CreateFromContinueStmt() {
    auto *tmp = new StmtNode();
    tmp->type = StmtType::continue_stmt;
    tmp->cur_id = StmtNode::GLOBAL_ID++;
    return tmp;
}

std::string *StmtNode::idTag() const {
    auto *tmp = new std::string(std::string("Stmt") + std::to_string(this->cur_id));
    return tmp;
}
