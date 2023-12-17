#include "TopStmtNode.hpp"

int TopStmtNode::GLOBAL_ID = 0;

TopStmtNode *TopStmtNode::CreateFromStmt(StmtNode *stmt) {
    auto *tmp = new TopStmtNode();
    tmp->stmt = stmt;
    tmp->type = TopStmtType::stmt_top_type;
    tmp->cur_id = TopStmtNode::GLOBAL_ID++;
    return tmp;
}

TopStmtNode *TopStmtNode::CreateFromFunctionDecl(FunctionStmtDeclNode *func_stmt_decl) {
    auto *tmp = new TopStmtNode();
    tmp->func_stmt_decl = func_stmt_decl;
    tmp->type = TopStmtType::function_top_type;
    tmp->cur_id = TopStmtNode::GLOBAL_ID++;
    return tmp;
}

TopStmtNode *TopStmtNode::CreateFromClassDecl(ClassStmtDeclNode *class_stmt_decl) {
    auto *tmp = new TopStmtNode();
    tmp->class_stmt_decl = class_stmt_decl;
    tmp->type = TopStmtType::class_top_type;
    tmp->cur_id = TopStmtNode::GLOBAL_ID++;
    return tmp;
}

TopStmtNode *TopStmtNode::CreateFromInterfaceDecl(InterfaceStmtDeclNode *interface_stmt_decl) {
    auto *tmp = new TopStmtNode();
    tmp->interface_stmt_decl = interface_stmt_decl;
    tmp->type = TopStmtType::interface_top_type;
    tmp->cur_id = TopStmtNode::GLOBAL_ID++;
    return tmp;
}

TopStmtNode *TopStmtNode::CreateFromTraitDecl(TraitStmtDeclNode *trait_stmt_decl) {
    auto *tmp = new TopStmtNode();
    tmp->trait_stmt_decl = trait_stmt_decl;
    tmp->type = TopStmtType::trait_top_type;
    tmp->cur_id = TopStmtNode::GLOBAL_ID++;
    return tmp;
}

std::string *TopStmtNode::idTag() const {
    auto* tmp = new std::string(std::string("TopStmt") + std::to_string(this->cur_id));
    return tmp;
}
