#include "ClassScopeContainer.hpp"

ClassScopeContainer *ClassScopeContainer::CreateContainer(string *id, vector<string *> variables,  vector<ConstDeclNode *> consts, vector<string *> extended, vector<string *> included, vector<string *> traits, vector<FunctionStmtDeclNode *> functions) {
  auto tmp = new ClassScopeContainer;
  tmp->id = id;
  tmp->variables = variables;
  tmp->consts = consts;
  tmp->extended = extended;
  tmp->included = included;
  tmp->traits = traits;
  tmp->functions = functions;
  return tmp;
}