#include "ClassScopeContainer.hpp"

ClassScopeContainer *ClassScopeContainer::CreateContainer(ClassStmtDeclNode *node, vector<ExprNode *> variables,  vector<ConstDeclNode *> consts, vector<FunctionStmtDeclNode *> functions) {
  auto tmp = new ClassScopeContainer;
  tmp->node = node;
  tmp->variables = variables;
  tmp->consts = consts;
  tmp->functions = functions;
  return tmp;
}