#include "ClassScopeContainer.hpp"

#include <utility>

ClassScopeContainer *
ClassScopeContainer::CreateContainer(string *id, vector<string *> variables, vector<ConstDeclNode *> consts,
                                     vector<string *> extended, vector<string *> included, vector<string *> traits,
                                     vector<FunctionStmtDeclNode *> functions) {
    auto tmp = new ClassScopeContainer;
    tmp->id = id;
    tmp->variables = std::move(variables);
    tmp->consts = std::move(consts);
    tmp->extended = std::move(extended);
    tmp->included = std::move(included);
    tmp->traits = std::move(traits);
    tmp->functions = std::move(functions);
    return tmp;
}
