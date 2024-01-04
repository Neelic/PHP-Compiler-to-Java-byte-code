#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../parser_classes/all_include.hpp"

using namespace std;

bool isDeclaredVariable(ExprNode *node, const vector<ExprNode *>& list);

bool isDeclaredConst(ConstDeclNode *node, const vector<ConstDeclNode *>& list);

bool isDeclaredFunction(FunctionStmtDeclNode *node, const vector<FunctionStmtDeclNode *> &list);

bool isDeclaredClass(ClassStmtDeclNode *node, const vector<ClassStmtDeclNode *>& list);

void inspectGlobalScope(StartNode* node);

#endif //SEMANTIC_H
