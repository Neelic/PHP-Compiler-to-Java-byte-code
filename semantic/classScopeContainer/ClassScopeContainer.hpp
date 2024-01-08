#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../parser_classes/all_include.hpp"

using namespace std;

class ClassStmtDeclNode;

class ClassScopeContainer {
public:

  ClassStmtDeclNode *node;
  vector<string *> variables;
  vector<ConstDeclNode *> consts;
  vector<FunctionStmtDeclNode *> functions;

  static ClassScopeContainer *CreateContainer(ClassStmtDeclNode *node, vector<ExprNode *> variables,  vector<ConstDeclNode *> consts, vector<FunctionStmtDeclNode *> functions);
};