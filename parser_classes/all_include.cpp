#include "all_include.hpp"

std::string GRAPH_STR("digraph Tree {\n");

void printTopStmtList(TopStmtList *node, std::string *parentId);

void printTopStmt(TopStmtNode *node, std::string *parentId);

void printStmt(StmtNode *node, std::string *parentId);

void printClassStmtDecl(ClassStmtDeclNode *node, std::string *parentId);

void printTraitStmtDecl(TraitStmtDeclNode *node, std::string *parentId);

void printInterfaceStmtDecl(TraitStmtDeclNode *node, std::string *parentId);

void printFuncStmtDecl(FunctionStmtDeclNode *node, std::string *parentId);

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
        printStmt(node->stmt, node->idTag());
    if (node->class_stmt_decl != nullptr)
        printClassStmtDecl(node->class_stmt_decl, node->idTag());
    if (node->trait_stmt_decl != nullptr)
        printTraitStmtDecl(node->trait_stmt_decl, node->idTag());
    if (node->interface_stmt_decl != nullptr)
        printInterfaceStmtDecl(node->trait_stmt_decl, node->idTag());
    if (node->func_stmt_decl != nullptr)
        printFuncStmtDecl(node->func_stmt_decl, node->idTag());
}

void printStmt(StmtNode *node, std::string *parentId) {
    GRAPH_STR += *node->idTag() + " [label=\"Stmt\"];\n";
    GRAPH_STR += *node->idTag() + " -> " + *parentId + "\n";

    if (node->const_decl != nullptr) {}
}

void printFuncStmtDecl(FunctionStmtDeclNode *node, std::string *parentId) {
}

void printInterfaceStmtDecl(TraitStmtDeclNode *node, std::string *parentId) {
}

void printTraitStmtDecl(TraitStmtDeclNode *node, std::string *basicString) {
}

void printClassStmtDecl(ClassStmtDeclNode *node, std::string *basicString) {
}
