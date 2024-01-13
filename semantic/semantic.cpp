#include "semantic.h"

string *file_name;

//Global scope vars
vector<string *> variables;
//Global scope consts
vector<ConstDeclNode *> consts;
//Global scope functions
vector<FunctionStmtDeclNode *> functions;
//Global scope classes
vector<ClassStmtDeclNode *> classes; //Здесь и в функциях заменил ClassStmtNode на ClassStmtDeclNode, тут же он нужен?
//Global scope interfaces
vector<InterfaceStmtDeclNode *> interfaces;
//Global scope traits
vector<TraitStmtDeclNode *> traits;
//Class scope properties
vector<ClassScopeContainer *> classProperties;

void inspectExpr(ExprNode *node, vector<string *> &variablesScope, const vector<ConstDeclNode *> &constsScope,
                 vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                 ContextType context = ContextType::noContext);

void inspectFunction(FunctionStmtDeclNode *node, string *parentId = nullptr);

void inspectFunctionDef(FunctionDefNode *node);

void inspectExprFunc(ExprFuncNode *node);

void inspectGetValueFunc(GetValueFuncNode *node);

void inspectClass(ClassStmtDeclNode *node);

void inspectClassDef(ClassDefNode *node);

void inspectClassStmt(ClassStmtNode *node, string *parentId);

void inspectClassExpr(ClassExprNode *node, string *parentId);

void inspectClassAccessModList(ClassAccessModList *list);

void inspectConstDecl(ConstDeclNode *node, string *parent_id = nullptr);

void inspectInterface(InterfaceStmtDeclNode *node);

void inspectInterfaceDef(InterfaceExprDefNode *node);

void inspectInterfaceStmt(InterfaceStmtNode *node, string *parentId);

void inspectTrait(TraitStmtDeclNode *node);

void inspectStmt(StmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                 vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                 ContextType context = ContextType::noContext);

void inspectIfStmt(IfStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                   vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                   ContextType context = ContextType::noContext);

void inspectSwitchStmt(SwitchStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                       vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                       ContextType context = ContextType::noContext);

void inspectCaseDefaultStmt(CaseDefaultStmtNode *node, vector<string *> &variablesScope,
                            vector<ConstDeclNode *> &constsScope,
                            vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                            ContextType context = ContextType::noContext);

void inspectStaticVar(StaticVarNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                      vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                      ContextType context = ContextType::noContext);

void inspectGlobalVar(GlobalVarNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                      vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                      ContextType context = ContextType::noContext);

void inspectWhileStmt(WhileStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                      vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                      ContextType context = ContextType::noContext);

void inspectDoWhileStmt(DoWhileStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                        vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                        ContextType context = ContextType::noContext);

void inspectForStmt(ForStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                    vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                    ContextType context = ContextType::noContext);

void inspectForEachStmt(ForEachStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                        vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass = false,
                        ContextType context = ContextType::noContext);

bool isDeclaredVariable(string *id, const vector<string *> &list) {
    if (id == nullptr) return false;

    return any_of(list.cbegin(), list.cend(),
                  [&id](auto &var) { return *var == *id; });
}

bool isDeclaredConst(string *id, const vector<ConstDeclNode *> &list) {
    if (id == nullptr) return false;

    return any_of(list.cbegin(), list.cend(),
                  [&id](auto &var) { return *var->id == *id; });
}

bool isDeclaredFunction(string *id, const vector<FunctionStmtDeclNode *> &list) {
    if (id == nullptr) return false;

    return any_of(list.cbegin(), list.cend(),
                  [&id](auto &var) {
                      return *var->function_def->func_id == *id;
                  });
}

bool isDeclaredClass(string *id, const vector<ClassStmtDeclNode *> &list) {
    if (id == nullptr) return false;

    return any_of(list.cbegin(), list.cend(),
                  [&id](auto &var) {
                      return *var->class_def->class_id == *id;
                  });
}

bool getClass(string *id) {
    if (id == nullptr) return false;

    for (auto &i: classes) {
        if (i->class_def->class_id == id)
            return i;
    }
}

bool isDeclaredInterface(string *id, const vector<InterfaceStmtDeclNode *> &list) {
    if (id == nullptr) return false;

    return any_of(list.cbegin(), list.cend(),
                  [&id](auto &var) {
                      return *var->expr_definition->id == *id;
                  });
}

bool isDeclaredTrait(string *id) {
    if (id == nullptr) return false;

    return any_of(traits.cbegin(), traits.cend(),
                  [&id](auto &var) {
                      return *var->id == *id;
                  });
}

// Определяет, является ли id стандартным типом
bool isStandartType(string *id) {
    if (id == nullptr) return false;

    // Тут просто сравниваю со всеми стандартными типами, дополнения приветствуются
    return id == new string("int") || id == new string("float") ||
           id == new string("string") || id == new string("bool") ||
           id == new string("array") || id == new string("object");
}

// Определяет, является ли id системной константой
bool isPredeclaredConst(string *id) {
    if (id == nullptr) return false;

    return id == new string("PHP_VERSION") || id == new string("PHP_MAJOR_VERSION") ||
           id == new string("PHP_MINOR_VERSION") || id == new string("PHP_RELEASE_VERSION") ||
           id == new string("PHP_VERSION_ID") || id == new string("PHP_EXTRA_VERSION") ||
           id == new string("PHP_ZTS") || id == new string("PHP_DEBUG") ||
           id == new string("PHP_MAXPATHLEN") || id == new string("PHP_OS") ||
           id == new string("PHP_OS_FAMILY") || id == new string("PHP_SAPI") ||
           id == new string("PHP_EOL") || id == new string("PHP_INT_MAX") ||
           id == new string("PHP_INT_MIN") || id == new string("PHP_INT_SIZE") ||
           id == new string("PHP_FLOAT_DIG") || id == new string("PHP_FLOAT_EPSILON") ||
           id == new string("PHP_FLOAT_MIN") || id == new string("PHP_FLOAT_MAX") ||
           id == new string("DEFAULT_INCLUDE_PATH") || id == new string("PEAR_INSTALL_DIR") ||
           id == new string("PEAR_EXTENSION_DIR") || id == new string("PHP_EXTENSION_DIR") ||
           id == new string("PHP_PREFIX") || id == new string("PHP_BINDIR") ||
           id == new string("PHP_MINOR_VERSION") || id == new string("PHP_RELEASE_VERSION") ||
           id == new string("PHP_BINARY") || id == new string("PHP_MANDIR") ||
           id == new string("PHP_LIBDIR") || id == new string("PHP_DATADIR") ||
           id == new string("PHP_SYSCONFDIR") || id == new string("PHP_LOCALSTATEDIR") ||
           id == new string("PHP_CONFIG_FILE_PATH") || id == new string("PHP_CONFIG_FILE_SCAN_DIR") ||
           id == new string("PHP_SHLIB_SUFFIX") || id == new string("PHP_FD_SETSIZE") ||
           id == new string("E_ERROR") || id == new string("E_WARNING") ||
           id == new string("E_PARSE") || id == new string("E_NOTICE") ||
           id == new string("E_CORE_ERROR") || id == new string("E_CORE_WARNING") ||
           id == new string("E_COMPILE_ERROR") || id == new string("E_COMPILE_WARNING") ||
           id == new string("E_USER_ERROR") || id == new string("E_USER_WARNING") ||
           id == new string("E_USER_NOTICE") || id == new string("E_RECOVERABLE_ERROR") ||
           id == new string("E_DEPRECATED") || id == new string("E_USER_DEPRECATED") ||
           id == new string("E_ALL") || id == new string("E_STRICT") ||
           id == new string("__COMPILER_HALT_OFFSET__") || id == new string("true") ||
           id == new string("false") || id == new string("null") ||
           id == new string("PHP_WINDOWS_EVENT_CTRL_C") || id == new string("PHP_WINDOWS_EVENT_CTRL_BREAK") ||
           id == new string("__LINE__") || id == new string("__FILE__") ||
           id == new string("__DIR__") || id == new string("__FUNCTION__") ||
           id == new string("__CLASS__") || id == new string("__TRAIT__") ||
           id == new string("__METHOD__") || id == new string("__NAMESPACE__") ||
           id == new string("ClassName::class");
}

// Определяет, является ли id системной переменной
bool isPredeclaredVariable(string *id) {
    if (id == nullptr) return false;

    return id == new string("GLOBALS") || id == new string("_SERVER") ||
           id == new string("_GET") || id == new string("_POST") ||
           id == new string("_FILES") || id == new string("_REQUEST") ||
           id == new string("_SESSION") || id == new string("_ENV") ||
           id == new string("_COOKIE") || id == new string("php_errormsg") ||
           id == new string("http_response_header") || id == new string("argc") ||
           id == new string("argv");
}


// Получить ClassScopeContainer по классу
ClassScopeContainer *getClassScopeContainer(string *parentId) {
    if (parentId == nullptr) return nullptr;

    for (auto &i: classProperties) {
        if (i->id == parentId)
            return i;
    }
}

void inspectGlobalScope(StartNode *node) {
    if (node == nullptr || node->top_stmt_list == nullptr) return;

    for (auto *tmp: node->top_stmt_list->vector) {
        switch (tmp->type) {
            case TopStmtType::stmt_top_type:
                inspectStmt(tmp->stmt, variables, consts, functions);
                break;
            case TopStmtType::class_top_type:
                break;
            case TopStmtType::function_top_type:
                inspectFunction(tmp->func_stmt_decl);
                break;
            case TopStmtType::interface_top_type:
                break;
            case TopStmtType::trait_top_type:
                break;
        }
    }
}


//Functions
void inspectFunction(FunctionStmtDeclNode *node, string *parentId) {

    if (node == nullptr) return;

    if (parentId != nullptr) {
        auto parentProperties = getClassScopeContainer(parentId);

        if (isDeclaredFunction(node->function_def->func_id, parentProperties->functions))
            throw runtime_error(
                    string("Fatal error: Cannot redeclare " + *node->function_def->func_id +
                           " (previously declared in " +
                           *file_name + ") in " + *file_name));

        parentProperties->functions.push_back(node);
    } else {
        if (isDeclaredFunction(node->function_def->func_id, functions))
            throw runtime_error(
                    string("Fatal error: Cannot redeclare " + *node->function_def->func_id +
                           " (previously declared in " +
                           *file_name + ") in " + *file_name));
        functions.push_back(node);
    }

    inspectFunctionDef(node->function_def);

    vector<string *> varList;

    varList.reserve(node->function_def->expr_func_list->vector.size());
    for (auto &tmp: node->function_def->expr_func_list->vector) {
        varList.push_back(tmp->get_value_func->id_value);
    }

    for (auto &i: node->stmt_list->vector) {
        auto tmp1 = varList;
        auto tmp2 = vector<ConstDeclNode *>();
        inspectStmt(i, tmp1, tmp2, functions);
    }
}

void inspectFunctionDef(FunctionDefNode *node) {
    if (node == nullptr) return;

    switch (node->type) {
        case FunctionDefType::no_type:
            break;
        case FunctionDefType::with_type:
            if (!isDeclaredClass(node->type_id, classes) &&
                !isDeclaredInterface(node->type_id, interfaces) &&
                !isStandartType(node->type_id))
                throw runtime_error(
                        string("Fatal error: Uncaught Error: Class \"" + *node->type_id + "\" not found in " +
                               *file_name));
            break;
    }

    for (auto &i: node->expr_func_list->vector) {
        inspectExprFunc(i);
    }
}

// Проверка параметров функции
void inspectExprFunc(ExprFuncNode *node) {
    if (node == nullptr) return;

    inspectGetValueFunc(node->get_value_func);

    switch (node->type) {
        case ExprFuncType::get_value_expr_type:
            break;
        case ExprFuncType::get_value_assign_expr_type:
            auto tmp1 = vector<string *>();
            auto tmp2 = vector<ConstDeclNode *>();
            inspectExpr(node->expr, tmp1, tmp2, functions);
            break;
    }
}

void inspectGetValueFunc(GetValueFuncNode *node) {
    if (node == nullptr) return;

    if (isPredeclaredVariable(node->id_value))
        throw runtime_error(
                string("Fatal error: Cannot re-assign auto-global variable " + *node->id_value + " in " + *file_name));

    switch (node->type) {
        case GetValueFuncType::no_ref_no_type:
            break;
        case GetValueFuncType::no_ref_with_type:
            if (!isDeclaredClass(node->id_type, classes) &&
                !isDeclaredInterface(node->id_type, interfaces) &&
                !isStandartType(node->id_type))
                throw runtime_error(
                        string("Fatal error: Uncaught Error: Class \"" + *node->id_type + "\" not found in " +
                               *file_name));
            break;
        case GetValueFuncType::with_ref_no_type:
            break;
        case GetValueFuncType::with_ref_with_type:
            if (!isDeclaredClass(node->id_type, classes) &&
                !isDeclaredInterface(node->id_type, interfaces) &&
                !isStandartType(node->id_type))
                throw runtime_error(
                        string("Fatal error: Uncaught Error: Class \"" + *node->id_type + "\" not found in " +
                               *file_name));
            break;
    }
}


//Classes
void inspectClass(ClassStmtDeclNode *node) {
    if (node == nullptr) return;

    // Добавляю в глобальный спискок пустой контейнер для хранения свойств и методов класса
    classProperties.push_back(ClassScopeContainer::CreateContainer(node->class_def->class_id, vector<string *>(),
                                                                   vector<ConstDeclNode *>(), vector<string *>(),
                                                                   vector<string *>(), vector<string *>(),
                                                                   vector<FunctionStmtDeclNode *>()));

    if (isDeclaredClass(node->class_def->class_id, classes) ||
        isDeclaredInterface(node->class_def->class_id, interfaces) ||
        isDeclaredTrait(node->class_def->class_id))
        throw runtime_error(string("Fatal error: Cannot declare class " + *node->class_def->class_id +
                                   ", because the name is already in use in " + *file_name));

    inspectClassDef(node->class_def);

    for (auto &i: node->class_stmt_list->vector) {
        inspectClassStmt(i, node->class_def->class_id);
    }
}

void inspectClassDef(ClassDefNode *node) {
    if (node == nullptr) return;

    auto classProps = getClassScopeContainer(node->class_id);

    switch (node->type) {
        case ClassDefType::class_def_type:
            break;
        case ClassDefType::extends_type:
            //Проверка, является ли наследуемый id объявленным классом
            if (!isDeclaredClass(node->extend_id, classes)) {
                // Если не является классом, является ли интерфейсом
                if (isDeclaredInterface(node->extend_id, interfaces))
                    throw runtime_error(string("Fatal error: Class " + *node->class_id + " cannot extend interface " +
                                               *node->extend_id + " in " + *file_name));
                    // Или является ли признаком
                else if (isDeclaredTrait(node->extend_id))
                    throw runtime_error(string("Fatal error: Class " + *node->class_id + " cannot extend trait " +
                                               *node->extend_id + " in " + *file_name));
                    // Иначе является неопознанным индентификатором
                else
                    throw runtime_error(
                            string("Fatal error: Uncaught Error: Class \"" + *node->extend_id + "\" not found in " +
                                   *file_name));
            } else {
                if (classProps != nullptr) {
                    classProps->extended.push_back(node->extend_id); // Добавляю id найденного класса в список extend
                }
            }

            break;
        case ClassDefType::implements_type:
            // Для каждого id в списке 
            for (int i = 0; i < node->impl_id_list->vector.size(); i++) {
                // Является ли объявленным интерфейсом
                if (!isDeclaredInterface(node->impl_id_list->vector[i], interfaces)) {
                    // Если не интерфейс, является ли классом или трейтом
                    if (isDeclaredClass(node->impl_id_list->vector[i], classes) ||
                        isDeclaredTrait(node->impl_id_list->vector[i]))
                        throw runtime_error(string("Fatal error: " + *node->class_id + " cannot implement " +
                                                   *node->impl_id_list->vector[i] + " - it is not an interface in " +
                                                   *file_name));
                        // Иначе неопознанный индентификатор
                    else
                        throw runtime_error(
                                string("Fatal error: Uncaught Error: Interface \"" + *node->impl_id_list->vector[i] +
                                       "\" not found in " + *file_name));
                } else if (classProps != nullptr)
                    classProps->extended.push_back(
                            node->impl_id_list->vector[i]); // Добавляю id найденного интерфейса в список includes
            }
            break;
        case ClassDefType::extends_implements_type:
            //Проверка extends
            if (!isDeclaredClass(node->extend_id, classes)) {
                if (isDeclaredInterface(node->extend_id, interfaces))
                    throw runtime_error(string("Fatal error: Class " + *node->class_id + " cannot extend interface " +
                                               *node->extend_id + " in " + *file_name));
                else if (isDeclaredTrait(node->extend_id))
                    throw runtime_error(string("Fatal error: Class " + *node->class_id + " cannot extend trait " +
                                               *node->extend_id + " in " + *file_name));
                else
                    throw runtime_error(
                            string("Fatal error: Uncaught Error: Class \"" + *node->extend_id + "\" not found in " +
                                   *file_name));
            } else if (classProps != nullptr)
                classProps->extended.push_back(node->extend_id); // Добавляю id найденного класса в список extend
            // Проверка includes
            for (int i = 0; i < node->impl_id_list->vector.size(); i++) {
                if (!isDeclaredInterface(node->impl_id_list->vector[i], interfaces)) {
                    if (isDeclaredClass(node->impl_id_list->vector[i], classes) ||
                        isDeclaredTrait(node->impl_id_list->vector[i]))
                        throw runtime_error(string("Fatal error: " + *node->class_id + " cannot implement " +
                                                   *node->impl_id_list->vector[i] + " - it is not an interface in " +
                                                   *file_name));
                    else
                        throw runtime_error(
                                string("Fatal error: Uncaught Error: Interface \"" + *node->impl_id_list->vector[i] +
                                       "\" not found in " + *file_name));
                } else if (classProps != nullptr)
                    classProps->included.push_back(
                            node->impl_id_list->vector[i]); // Добавляю id найденного интерфейса в список includes
            }
            break;
    }
}


void inspectClassStmt(ClassStmtNode *node, string *parentId) {
    if (node == nullptr) return;

    auto parentProperties = getClassScopeContainer(parentId);
    bool isAbstract = false;

    switch (node->type) {
        case ClassStmtType::class_expr_stmt_type:
            inspectClassExpr(node->class_expr, parentId);
            break;
        case ClassStmtType::function_decl_type:
            inspectClassAccessModList(node->access_mod);
            inspectFunction(node->function_stmt_decl, parentId);
            if (parentProperties != nullptr) parentProperties->functions.push_back(node->function_stmt_decl);
            break;
        case ClassStmtType::function_def:

            inspectClassAccessModList(node->access_mod);

            //Проверяю, есть ли в модификатор abstract, т.к. заголовок функции без тела может быть только абстрактным
            isAbstract = any_of(node->access_mod->vector.cbegin(), node->access_mod->vector.cend(),
                                [](auto &var) {
                                    return var->access_mod == ClassAccessMod::abstract_node;
                                });
            if (!isAbstract) {
                throw runtime_error(
                        string("Fatal error: Non-abstract method " + *parentId + "::" + *node->function_def->func_id +
                               "() must contain body in" + *file_name));
            }

            // Проверка на переопределение
            if (parentProperties == nullptr) throw length_error("null error");
            if (isDeclaredFunction(node->function_def->func_id, parentProperties->functions))
                throw runtime_error(
                        string("Fatal error: Cannot redeclare " + *parentId + "::" + *node->function_def->func_id +
                               "() in " + *file_name));

            //Здесть создаю нод FunctionStmtDecl только с заголовком, чтобы можно было сохранять. В списке функций хранить ноды имеет смысл, я считаю
            if (parentProperties != nullptr)
                parentProperties->functions.push_back(FunctionStmtDeclNode::CreateNode(node->function_def, nullptr));

            inspectFunctionDef(node->function_def);
            break;
        case ClassStmtType::id_list_type:
            for (auto i: node->id_list->vector) {
                if (!isDeclaredTrait(i)) {
                    if (isDeclaredClass(i, classes) || isDeclaredInterface(i, interfaces))
                        throw runtime_error(string("Fatal error: " + *parentId + " cannot use " +
                                                   *i + " - it is not an trait in " +
                                                   *file_name));
                    else
                        throw runtime_error(
                                string("Fatal error: Trait \"" + *i +
                                       "\" not found in " + *file_name));
                }
            }
            break;
    }
}

void inspectClassExpr(ClassExprNode *node, string *parentId) {
    if (node == nullptr) return;

    auto parentProperties = getClassScopeContainer(parentId);

    switch (node->type) {
        case ClassExprType::get_value_class_type:
            inspectClassAccessModList(node->access_mod_list);
            //Проверка на переопределение будет на рантайме
            break;
        case ClassExprType::get_value_assign_class_type:
            inspectClassAccessModList(node->access_mod_list);
            if (parentProperties != nullptr) {
                //Проверка на переопределение будет на рантайме
                inspectExpr(node->expr, parentProperties->variables, parentProperties->consts,
                            parentProperties->functions,
                            true);
            }
            break;
        case ClassExprType::const_class_type:
            //TODO: добавить проверку объявления констант
            break;
    }
}

void inspectClassAccessModList(ClassAccessModList *list) {
    if (list == nullptr) return;

    // Здесь пытаюсь проверить спискок модов на дубликаты
    auto noRepeatList = list->vector;

    sort(noRepeatList.begin(), noRepeatList.end());
    auto i = unique(noRepeatList.begin(), noRepeatList.end());

    if (i != list->vector.end()) {
        throw runtime_error(string("Fatal error: Multiple access type modifiers are not allowed in " + *file_name));
    }
}


// Проверка объявления констант
void inspectConstDecl(ConstDeclNode *node, string *parent_id) {
    if (node == nullptr) return;

    // Если константа объявлена и в классе, и в одном из трейтов, это будет ошибкой только тогда, когда значения будут разными. Так что наверное проверяем на рантайме

    if (parent_id != nullptr) {
        auto parentProperties = getClassScopeContainer(parent_id);

        if (isDeclaredConst(node->id, parentProperties->consts))
            cout << "Warning: Constant " << *node->id << " already defined in " << *file_name << endl;
        else parentProperties->consts.push_back(node);

    } else {
        if (isDeclaredConst(node->id, consts))
            cout << "Warning: Constant " << *node->id << " already defined in " << *file_name << endl;
        else consts.push_back(node);
    }

    auto tmp1 = vector<string *>();
    auto tmp2 = vector<ConstDeclNode *>();
    auto tmp3 = vector<FunctionStmtDeclNode *>();

    inspectExpr(node->expr, tmp1, tmp2, tmp3, parent_id != nullptr);
}


//Interfaces 
void inspectInterface(InterfaceStmtDeclNode *node) {
    if (node == nullptr) return;

    classProperties.push_back(ClassScopeContainer::CreateContainer(node->expr_definition->id,
                                                                   vector<string *>(),
                                                                   vector<ConstDeclNode *>(),
                                                                   vector<string *>(),
                                                                   vector<string *>(),
                                                                   vector<string *>(),
                                                                   vector<FunctionStmtDeclNode *>()));

    if (isDeclaredInterface(node->expr_definition->id, interfaces) ||
        isDeclaredClass(node->expr_definition->id, classes) ||
        isDeclaredTrait(node->expr_definition->id)) {
        throw runtime_error(string("Fatal error: Cannot declare interface " + *node->expr_definition->id +
                                   ", because the name is already in use in " + *file_name));
    }

    inspectInterfaceDef(node->expr_definition);

    for (auto i: node->stmt_list->vector) {
        inspectInterfaceStmt(i, node->expr_definition->id);
    }

}

void inspectInterfaceDef(InterfaceExprDefNode *node) {
    if (node == nullptr) return;

    auto interfaceProps = getClassScopeContainer(node->id);

    if (node->id_extended_list != nullptr) {

        for (auto i: node->id_extended_list->vector) {
            if (!isDeclaredInterface(i, interfaces)) {
                if (isDeclaredClass(i, classes) ||
                    isDeclaredTrait(i))
                    throw runtime_error(string("Fatal error: " + *node->id + " cannot implement " +
                                               *i + " - it is not an interface in " +
                                               *file_name));
                else
                    throw runtime_error(
                            string("Fatal error: Uncaught Error: Interface \"" + *i +
                                   "\" not found in " + *file_name));
            } else {
                if (interfaceProps == nullptr) throw length_error("null error");
                interfaceProps->included.push_back(i); // Добавляю id найденного интерфейса в список includes
            }

            // Проверяю на дубликат в списке интерфейсов
            for (auto j: interfaceProps->included) {
                if (i == j)
                    throw runtime_error(
                            string("Fatal error: Interface a cannot implement previously implemented interface " + *i +
                                   " in " + *file_name));
            }
        }
    }
}

void inspectInterfaceStmt(InterfaceStmtNode *node, string *parentId) {
    if (node == nullptr) return;

    if (node->access_mod != nullptr) {
        inspectClassAccessModList(node->access_mod);
        for (auto i: node->access_mod->vector) {
            if (i->access_mod == ClassAccessMod::abstract_node)
                throw runtime_error(
                        string("Fatal error: Interface method " + *parentId + "::" + *node->function_def->func_id +
                               "() must not be abstract in " + *file_name));
        }
    }

    auto interfaceProps = getClassScopeContainer(parentId);

    if (interfaceProps == nullptr) throw length_error("null error");

    if (isDeclaredFunction(node->function_def->func_id, interfaceProps->functions))
        throw runtime_error(
                string("Fatal error: Cannot redeclare " + *parentId + "::" + *node->function_def->func_id + "() in " +
                       *file_name));

    inspectFunctionDef(node->function_def);
    interfaceProps->functions.push_back(FunctionStmtDeclNode::CreateNode(node->function_def, nullptr));
}


//Traits
void inspectTrait(TraitStmtDeclNode *node) {
    if (node == nullptr) return;

    classProperties.push_back(ClassScopeContainer::CreateContainer(node->id,
                                                                   vector<string *>(),
                                                                   vector<ConstDeclNode *>(),
                                                                   vector<string *>(),
                                                                   vector<string *>(),
                                                                   vector<string *>(),
                                                                   vector<FunctionStmtDeclNode *>()));

    if (isDeclaredInterface(node->id, interfaces) ||
        isDeclaredClass(node->id, classes) ||
        isDeclaredTrait(node->id)) {
        throw runtime_error(
                string("Fatal error: Cannot declare trait " + *node->id + ", because the name is already in use in " +
                       *file_name));
    }

    for (auto i: node->stmt_list->vector) {
        inspectClassStmt(i, node->id);
    }
}


//Statements
void inspectStmt(StmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                 vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    switch (node->type) {
        case StmtType::expr:
            inspectExpr(node->expr_left, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case StmtType::for_stmt:
            inspectForStmt(node->for_stmt, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case StmtType::foreach_stmt:
            inspectForEachStmt(node->foreach_stmt, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case StmtType::do_while_stmt:
            inspectDoWhileStmt(node->do_while_stmt, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case StmtType::while_stmt:
            inspectWhileStmt(node->while_stmt, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case StmtType::break_stmt:
            if (context != ContextType::inLoop && context != ContextType::inSwitch)
                throw runtime_error(
                        string("Fatal error: 'break' not in the 'loop' or 'switch' context in " + *file_name));
            break;
        case StmtType::const_decl:
            for (auto i: node->const_decl->vector) {
                inspectConstDecl(i);
            }
            break;
        case StmtType::continue_stmt:
            if (context != ContextType::inLoop && context != ContextType::inSwitch)
                throw runtime_error(
                        string("Fatal error: 'break' not in the 'loop' or 'switch' context in " + *file_name));
            break;
        case StmtType::global_var:
            for (auto i: node->global_var->vector) {
                inspectGlobalVar(i, variablesScope, constsScope, functionsScope, isInClass, context);
            }
            break;
        case StmtType::html_stmt:
            node->type = StmtType::t_echo_stmt;
            node->expr_right = ExprNode::CreateFromStringValue(node->html_stmt->html);
            inspectExpr(node->expr_right, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case StmtType::if_stmt:
            inspectIfStmt(node->if_stmt, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case StmtType::return_stmt:
            inspectExpr(node->expr_left, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case StmtType::static_var:
            for (auto i: node->static_var->vector) {
                inspectStaticVar(i, variablesScope, constsScope, functionsScope, isInClass, context);
            }
            break;
        case StmtType::stmt_list:
            for (auto i: node->stmtList->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope, isInClass, context);
            }
            break;
        case StmtType::switch_stmt:
            inspectSwitchStmt(node->switch_stmt, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case StmtType::t_echo_stmt:
            node->expr_right = ExprNode::CreateFromStringCast(node->expr_right);
            inspectExpr(node->expr_right, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
    }
}


//If statement
void inspectIfStmt(IfStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                   vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    inspectExpr(node->expr, variablesScope, constsScope, functionsScope, isInClass, context);

    switch (node->type) {
        case IfStmtType::only_if:
            inspectStmt(node->stmt_main, variablesScope, constsScope, functionsScope,
                        isInClass, ContextType::inIf);
            break;
        case IfStmtType::if_else:
            inspectStmt(node->stmt_main, variablesScope, constsScope, functionsScope,
                        isInClass, ContextType::inIf);
            inspectStmt(node->stmt_else, variablesScope, constsScope, functionsScope,
                        isInClass, ContextType::inIf);
            break;
        case IfStmtType::end_if:
            for (auto i: node->stmtListMain->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope,
                            isInClass, ContextType::inIf);
            }
            break;
        case IfStmtType::if_else_endif:
            for (auto i: node->stmtListMain->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope,
                            isInClass, ContextType::inIf);
            }
            for (auto i: node->stmtListElse->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope,
                            isInClass, ContextType::inIf);
            }
            break;
        case IfStmtType::if_else_list_endif:
            for (auto i: node->stmtListMain->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope,
                            isInClass, ContextType::inIf);
            }
            if (node->listElse != nullptr)
                for (auto i: node->listElse->vector) {
                    inspectIfStmt(i, variablesScope, constsScope, functionsScope,
                                  isInClass, ContextType::inIf);
                }
            break;
    }

}

//SwitchStmt
void inspectSwitchStmt(SwitchStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                       vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    inspectExpr(node->expr, variablesScope, constsScope, functionsScope, isInClass, context);

    switch (node->type) {
        case SwitchStmtType::just_switch:
            break;
        case SwitchStmtType::switch_default:
            for (auto i: node->defaultStmtList->vector) {
                inspectCaseDefaultStmt(i, variablesScope, constsScope, functionsScope, isInClass,
                                       ContextType::inSwitch);
            }
            break;
        case SwitchStmtType::switch_default_endswitch:
            for (auto i: node->defaultStmtList->vector) {
                inspectCaseDefaultStmt(i, variablesScope, constsScope, functionsScope, isInClass,
                                       ContextType::inSwitch);
            }
            break;
    }

}

void inspectCaseDefaultStmt(CaseDefaultStmtNode *node, vector<string *> &variablesScope,
                            vector<ConstDeclNode *> &constsScope, vector<FunctionStmtDeclNode *> &functionsScope,
                            bool isInClass, ContextType context) {
    if (node == nullptr) return;

    for (auto i: node->stmtList->vector) {
        inspectStmt(i, variablesScope, constsScope, functionsScope, isInClass, ContextType::inSwitch);
    }

    switch (node->type) {
        case CaseDefaultType::case_stmt:
            inspectExpr(node->expr, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case CaseDefaultType::default_stmt:
            break;
        case CaseDefaultType::finally_stmt:
            break;
    }

}


//For statement
void inspectForStmt(ForStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                    vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    // Создаю список для переменных внутри цикла
    auto forVariableScope = variablesScope;

    inspectExpr(node->expr_left, variablesScope, constsScope, functionsScope, isInClass, context);

    // Добавляю переменную, объявленную в заголовке цикла
    forVariableScope.push_back(node->expr_left->id);

    inspectExpr(node->expr_central, variablesScope, constsScope, functionsScope, isInClass, context);

    inspectExpr(node->expr_right, variablesScope, constsScope, functionsScope, isInClass, context);

    switch (node->type) {
        case ForStmtType::for_stmt_type:
            inspectStmt(node->stmt, forVariableScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            break;
        case ForStmtType::for_end_stmt_type:
            for (auto i: node->stmtList->vector) {
                inspectStmt(i, forVariableScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            }
            break;
    }
}


//For each statement
void inspectForEachStmt(ForEachStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                        vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    // Cписок для переменных внутри цикла
    auto foreachVariableScope = variablesScope;

    inspectExpr(node->expr_left, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);

    inspectExpr(node->expr_right, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);

    // Добавляю переменную, объявленную в заголовке цикла
    foreachVariableScope.push_back(node->expr_right->id);

    switch (node->type) {
        case ForEachStmtType::foreach_stmt_type:
            inspectStmt(node->stmt, foreachVariableScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            break;
        case ForEachStmtType::foreach_r_double_arrow_stmt_type:
            foreachVariableScope.push_back(node->id);
            inspectStmt(node->stmt, foreachVariableScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            break;
        case ForEachStmtType::foreach_r_double_arrow_pointer_stmt_type:
            foreachVariableScope.push_back(node->id);
            inspectStmt(node->stmt, foreachVariableScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            break;
        case ForEachStmtType::end_foreach_stmt_type:
            for (auto i: node->stmtList->vector) {
                inspectStmt(node->stmt, foreachVariableScope, constsScope, functionsScope, isInClass,
                            ContextType::inLoop);
            }
            break;
        case ForEachStmtType::end_foreach_r_double_arrow_stmt_type:
            foreachVariableScope.push_back(node->id);
            for (auto i: node->stmtList->vector) {
                inspectStmt(node->stmt, foreachVariableScope, constsScope, functionsScope, isInClass,
                            ContextType::inLoop);
            }
            break;
        case ForEachStmtType::end_foreach_r_double_arrow_pointer_stmt_type:
            foreachVariableScope.push_back(node->id);
            for (auto i: node->stmtList->vector) {
                inspectStmt(i, foreachVariableScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            }
            break;
    }
}


// While statement
void inspectWhileStmt(WhileStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                      vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    inspectExpr(node->expr, variablesScope, constsScope, functionsScope, isInClass, context);

    switch (node->type) {
        case WhileStmtType::while_stmt_type:
            inspectStmt(node->stmt, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            break;
        case WhileStmtType::end_while_stmt_type:
            for (auto i: node->stmtList->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            }
            break;
    }
}

void inspectDoWhileStmt(DoWhileStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                        vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    inspectExpr(node->expr, variablesScope, constsScope, functionsScope, isInClass, context);

    inspectStmt(node->stmt, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
}


//Expression
void inspectExpr(ExprNode *node, vector<string *> &variablesScope, const vector<ConstDeclNode *> &constsScope,
                 vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    switch (node->exprType) {
        case ExprType::assign_op:
            //if re-assign $this
            if (*node->left->id == "this" && node->get_value != nullptr && node->get_value->count == 1)
                //Throw fatal error
                throw runtime_error(string("Fatal error: Cannot re-assign $this in " + *file_name));
            //if use right-side variable is not declared
            if (node->right->exprType == ExprType::variable && !isDeclaredVariable(node->right->id, variables)) {
                cout << "Warning: Undefined variable $" << *node->right->id << " in " << *file_name << endl;
                node->right = ExprNode::CreateFromAssignOp(node->right, ExprNode::CreateFromNull());
                variables.push_back(node->right->left->id);
            }

            inspectExpr(node->left, variablesScope, constsScope, functionsScope, isInClass);
            inspectExpr(node->right, variablesScope, constsScope, functionsScope, isInClass);
            break;
        case ExprType::assign_ref_op:
            if (*node->left->id == "this" && node->get_value != nullptr && node->get_value->count == 1)
                //Throw fatal error
                throw runtime_error(string("Fatal error: Cannot re-assign $this in " + *file_name));
            //if use right-side variable is not declared
            if (node->right->exprType == ExprType::variable && !isDeclaredVariable(node->right->id, variables)) {
                cout << "Warning: Undefined variable $" << *node->right->id << " in " << *file_name << endl;
                node->right = ExprNode::CreateFromAssignOp(node->right, ExprNode::CreateFromNull());
                variables.push_back(node->right->left->id);
            }

            inspectExpr(node->left, variablesScope, constsScope, functionsScope, isInClass);
            inspectExpr(node->right, variablesScope, constsScope, functionsScope, isInClass);
            break;
        case ExprType::class_field_by_ref_op:
            //TODO добавить еще подобных кейз случаев
            inspectExpr(node->left, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case ExprType::this_keyword:
            if (!isInClass)
                throw runtime_error(
                        "Fatal error: Uncaught error: Using $this when in not in object context in " + *file_name);
            break;
    }
}
