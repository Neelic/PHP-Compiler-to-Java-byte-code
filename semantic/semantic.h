#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../parser_classes/all_include.hpp"

using namespace std;

bool isDeclaredVariable(string *id, const vector<ExprNode *>& list);

bool isDeclaredConst(string *id, const vector<ConstDeclNode *>& list);

bool isDeclaredFunction(string *id, const vector<FunctionStmtDeclNode *> &list);

bool isDeclaredClass(string *id, const vector<ClassStmtDeclNode *>& list);

bool isDeclaredTrait(string *id);

bool isStandartType(string *id);

bool isPredeclaredConst(string *id);

bool isPredeclaredVariable(string *id);

void inspectGlobalScope(StartNode* node);

#endif //SEMANTIC_H
