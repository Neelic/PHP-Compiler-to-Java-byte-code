#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../parser_classes/all_include.hpp"

using namespace std;

class ClassStmtDeclNode;

class ClassScopeContainer {
public:

    string *id;
    vector<string *> variables;
    vector<ConstDeclNode *> consts;
    vector<string *> extended; //Для получения функций, переменных и констант от родителя
    vector<string *> included; //Для получения функций, переменных и констант от наследованных интерфейсов
    vector<string *> traits; //Для получения функций, переменных и констант из трейтов
    vector<FunctionStmtDeclNode *> functions;

    static ClassScopeContainer *
    CreateContainer(string *id, vector<string *> variables, vector<ConstDeclNode *> consts,
                    vector<string *> extended, vector<string *> included, vector<string *> traits,
                    vector<FunctionStmtDeclNode *> functions);
};