#include "semantic.h"

string *file_name;
string currentObjectName;

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

void inspectClassStmt(ClassStmtNode *node, string *parentId, bool isAbstractClass = false);

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

void inspectExprList(ExprList *node, vector<string *> &variablesScope, const vector<ConstDeclNode *> &constsScope,
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

//bool getClass(string *id) {
//    if (id == nullptr) return false;
//
//    for (auto &i: classes) {
//        if (i->class_def->class_id == id)
//            return i;
//    }
//}

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
    return *id == string("int") || *id == string("float") ||
           *id == string("string") || *id == string("bool") ||
           *id == string("array") || *id == string("object");
}

// Определяет, является ли id системной константой
bool isPredeclaredConst(string *id) {
    if (id == nullptr) return false;

    return *id == string("PHP_VERSION") || *id == string("PHP_MAJOR_VERSION") ||
           *id == string("PHP_MINOR_VERSION") || *id == string("PHP_RELEASE_VERSION") ||
           *id == string("PHP_VERSION_ID") || *id == string("PHP_EXTRA_VERSION") ||
           *id == string("PHP_ZTS") || *id == string("PHP_DEBUG") ||
           *id == string("PHP_MAXPATHLEN") || *id == string("PHP_OS") ||
           *id == string("PHP_OS_FAMILY") || *id == string("PHP_SAPI") ||
           *id == string("PHP_EOL") || *id == string("PHP_INT_MAX") ||
           *id == string("PHP_INT_MIN") || *id == string("PHP_INT_SIZE") ||
           *id == string("PHP_FLOAT_DIG") || *id == string("PHP_FLOAT_EPSILON") ||
           *id == string("PHP_FLOAT_MIN") || *id == string("PHP_FLOAT_MAX") ||
           *id == string("DEFAULT_INCLUDE_PATH") || *id == string("PEAR_INSTALL_DIR") ||
           *id == string("PEAR_EXTENSION_DIR") || *id == string("PHP_EXTENSION_DIR") ||
           *id == string("PHP_PREFIX") || *id == string("PHP_BINDIR") ||
           *id == string("PHP_MINOR_VERSION") || *id == string("PHP_RELEASE_VERSION") ||
           *id == string("PHP_BINARY") || *id == string("PHP_MANDIR") ||
           *id == string("PHP_LIBDIR") || *id == string("PHP_DATADIR") ||
           *id == string("PHP_SYSCONFDIR") || *id == string("PHP_LOCALSTATEDIR") ||
           *id == string("PHP_CONFIG_FILE_PATH") || *id == string("PHP_CONFIG_FILE_SCAN_DIR") ||
           *id == string("PHP_SHLIB_SUFFIX") || *id == string("PHP_FD_SETSIZE") ||
           *id == string("E_ERROR") || *id == string("E_WARNING") ||
           *id == string("E_PARSE") || *id == string("E_NOTICE") ||
           *id == string("E_CORE_ERROR") || *id == string("E_CORE_WARNING") ||
           *id == string("E_COMPILE_ERROR") || *id == string("E_COMPILE_WARNING") ||
           *id == string("E_USER_ERROR") || *id == string("E_USER_WARNING") ||
           *id == string("E_USER_NOTICE") || *id == string("E_RECOVERABLE_ERROR") ||
           *id == string("E_DEPRECATED") || *id == string("E_USER_DEPRECATED") ||
           *id == string("E_ALL") || *id == string("E_STRICT") ||
           *id == string("__COMPILER_HALT_OFFSET__") || *id == string("true") ||
           *id == string("false") || *id == string("null") ||
           *id == string("PHP_WINDOWS_EVENT_CTRL_C") || *id == string("PHP_WINDOWS_EVENT_CTRL_BREAK") ||
           *id == string("__LINE__") || *id == string("__FILE__") ||
           *id == string("__DIR__") || *id == string("__FUNCTION__") ||
           *id == string("__CLASS__") || *id == string("__TRAIT__") ||
           *id == string("__METHOD__") || *id == string("__NAMESPACE__") ||
           *id == string("ClassName::class") || *id == string("true") || *id == string("false");
}

// Определяет, является ли id системной переменной
bool isPredeclaredVariable(string *id) {
    if (id == nullptr) return false;

    return *id == string("GLOBALS") || *id == string("_SERVER") ||
           *id == string("_GET") || *id == string("_POST") ||
           *id == string("_FILES") || *id == string("_REQUEST") ||
           *id == string("_SESSION") || *id == string("_ENV") ||
           *id == string("_COOKIE") || *id == string("php_errormsg") ||
           *id == string("http_response_header") || *id == string("argc") ||
           *id == string("argv");
}


// Получить ClassScopeContainer по классу
ClassScopeContainer *getClassScopeContainer(string *parentId) {
    if (parentId == nullptr) return nullptr;

    ClassScopeContainer *res;

    for (auto &i: classProperties) {
        if (*i->id == *parentId)
            res = i;
    }
    return res;
}

void inspectGlobalScope(StartNode *node) {
    if (node == nullptr || node->top_stmt_list == nullptr) return;

    for (auto *tmp: node->top_stmt_list->vector) {
        switch (tmp->type) {
            case TopStmtType::stmt_top_type:
                inspectStmt(tmp->stmt, variables, consts, functions);
                break;
            case TopStmtType::class_top_type:
                inspectClass(tmp->class_stmt_decl);
                break;
            case TopStmtType::function_top_type:
                inspectFunction(tmp->func_stmt_decl);
                break;
            case TopStmtType::interface_top_type:
                inspectInterface(tmp->interface_stmt_decl);
                break;
            case TopStmtType::trait_top_type:
                inspectTrait(tmp->trait_stmt_decl);
                break;
        }
    }

    // Добавляю класс скоп для глобального класса, в id пусто т.к. не может появиться класса с пустым именем
    classProperties.push_back(
            ClassScopeContainer::CreateContainer(new string(""), variables, consts, vector<string *>(),
                                                 vector<string *>(), vector<string *>(), functions));
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

    if (node->function_def->expr_func_list != nullptr) {

        varList.reserve(node->function_def->expr_func_list->vector.size());
        for (auto &tmp: node->function_def->expr_func_list->vector) {
            varList.push_back(tmp->get_value_func->id_value);
        }

    }


    if (node->stmt_list == nullptr) return;

    for (auto &i: node->stmt_list->vector) {
        auto tmp1 = varList;
        auto tmp2 = vector<ConstDeclNode *>();
        inspectStmt(i, tmp1, tmp2, functions, (parentId != nullptr),
                    inFunction); // Если parent id не пуст, значит, в классе.
    }
}

void inspectFunctionDef(FunctionDefNode *node) {
    if (node == nullptr) return;

    switch (node->type) {
        case FunctionDefType::no_type:
            break;
        case FunctionDefType::with_type:
            break;
    }

    if (node->expr_func_list == nullptr) return;

    ExprFuncNode *prevNode = nullptr;

    for (auto &i: node->expr_func_list->vector) {
        if (prevNode != nullptr && prevNode->type == get_value_assign_expr_type && i->type == get_value_expr_type) {
            cout << "Deprecated: Optional parameter $" << *prevNode->get_value_func->id_value
                 << " declared before required parameter $" << *i->get_value_func->id_value
                 << " is implicitly treated as a required parameter in " << *file_name << endl;
            prevNode->type = get_value_expr_type; // Судя по предупреждению, пхп просто преобразует объявленный параметр к обязательному, то бишь без значения по умолчанию
        }
        inspectExprFunc(i);
        prevNode = i;
    }

    delete prevNode;
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
            break;
        case GetValueFuncType::with_ref_no_type:
            break;
        case GetValueFuncType::with_ref_with_type:
            break;
    }
}


//Classes
void inspectClass(ClassStmtDeclNode *node) {
    if (node == nullptr) return;
    currentObjectName = *node->class_def->class_id;

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

    classes.push_back(node);

    if (node->class_stmt_list == nullptr) {
        currentObjectName = "";
        return;
    }

    for (auto &i: node->class_stmt_list->vector) {
        inspectClassStmt(i, node->class_def->class_id, node->type == abstract_type);
    }

    currentObjectName = "";
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

                } else if (classProps != nullptr)
                    classProps->included.push_back(
                            node->impl_id_list->vector[i]); // Добавляю id найденного интерфейса в список includes
            }
            break;
    }
}


void inspectClassStmt(ClassStmtNode *node, string *parentId, bool isAbstractClass) {
    if (node == nullptr) return;

    auto parentProperties = getClassScopeContainer(parentId);
    bool isAbstract = false;

    switch (node->type) {
        case ClassStmtType::class_expr_stmt_type:
            inspectClassExpr(node->class_expr, parentId);
            break;
        case ClassStmtType::function_decl_type:
            inspectClassAccessModList(node->access_mod);
            if (node->access_mod != nullptr) {

                for (auto &i: node->access_mod->vector) {
                    switch (i->access_mod) {
                        case abstract_node:
                            break;
                        case read_only_node:
                            throw runtime_error(
                                    string("Fatal error: Cannot use 'readonly' as method modifier in " + *file_name));
                    }
                }

            }
            inspectFunction(node->function_stmt_decl, parentId);
            if (parentProperties != nullptr) parentProperties->functions.push_back(node->function_stmt_decl);
            break;
        case ClassStmtType::function_def:

            inspectClassAccessModList(node->access_mod);

            if (node->access_mod != nullptr) {

                for (auto &i: node->access_mod->vector) {
                    switch (i->access_mod) {
                        case abstract_node:
                            isAbstract = true; //Проверяю, есть ли в модификатор abstract, т.к. заголовок функции без тела может быть только абстрактным
                            break;
                        case read_only_node:
                            throw runtime_error(
                                    string("Fatal error: Cannot use 'readonly' as method modifier in " + *file_name));
                    }
                }

            }

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

            if (node->access_mod_list == nullptr) break;

            for (auto &i: node->access_mod_list->vector) {
                switch (i->access_mod) {
                    case abstract_node:
                        throw runtime_error(
                                string("Fatal error: Properties cannot be declared abstract in " + *file_name));
                    case final_node:
                        throw runtime_error(string("Cannot declare property " + *parentId + "::$ " + *node->id +
                                                   " final, the final modifier is allowed only for methods, classes, and class constants in " +
                                                   *file_name));
                    case read_only_node:
                        if (node->id_type == nullptr) {
                            throw runtime_error(
                                    string("Fatal error: Readonly property " + *parentId + "::$ " + *node->id +
                                           " must have type in " + *file_name));
                        }
                        break;
                }
            }
            break;
        case ClassExprType::get_value_assign_class_type:

            if (parentProperties != nullptr) {
                //Проверка на переопределение будет на рантайме
                inspectExpr(node->expr, parentProperties->variables, parentProperties->consts,
                            parentProperties->functions,
                            true);
            }

            if (node->access_mod_list == nullptr) break;

            inspectClassAccessModList(node->access_mod_list);

            for (auto &i: node->access_mod_list->vector) {
                switch (i->access_mod) {
                    case abstract_node:
                        throw runtime_error(
                                string("Fatal error: Properties cannot be declared abstract in " + *file_name));
                    case final_node:
                        throw runtime_error(string("Cannot declare property " + *parentId + "::$ " + *node->id +
                                                   " final, the final modifier is allowed only for methods, classes, and class constants in " +
                                                   *file_name));
                    case read_only_node:
                        if (node->id_type == nullptr) {
                            throw runtime_error(
                                    string("Fatal error: Readonly property " + *parentId + "::$ " + *node->id +
                                           " must have type in " + *file_name));
                        } else {
                            throw runtime_error(
                                    string("Fatal error: Readonly property " + *parentId + "::$ " + *node->id +
                                           " cannot have default value in " + *file_name));
                        }
                }
            }
            break;
        case ClassExprType::const_class_type:
            inspectClassAccessModList(node->access_mod_list);

            for (auto &i: node->const_decl_list->vector) {
                inspectConstDecl(i, parentId);
            }

            for (auto &i: node->access_mod_list->vector) {
                switch (i->access_mod) {
                    case abstract_node:
                        throw runtime_error(
                                string("Fatal error: Cannot use 'abstract' as constant modifier in " + *file_name));
                    case static_node:
                        throw runtime_error(
                                string("Fatal error: Cannot use 'static' as constant modifier in " + *file_name));
                    case read_only_node:
                        throw runtime_error(
                                string("Fatal error: Cannot use 'readonly' as constant modifier in " + *file_name));
                }
            }
            break;
    }
}

void inspectClassAccessModList(ClassAccessModList *list) {
    if (list == nullptr) return;

    // Здесь пытаюсь проверить спискок модов на дубликаты

    ClassAccessModNode *prevNode = nullptr;

    for (auto &i: list->vector) {
        if (prevNode != nullptr && i->access_mod == prevNode->access_mod) {
            throw runtime_error(string("Fatal error: Multiple access type modifiers are not allowed in " + *file_name));
        } else {
            prevNode = i;
        }
    }
}


// Проверка объявления констант
void inspectConstDecl(ConstDeclNode *node, string *parent_id) {
    if (node == nullptr) return;

    // Если константа объявлена и в классе, и в одном из трейтов, это будет ошибкой только тогда, когда значения будут разными. Так что наверное проверяем на рантайме

    if (parent_id != nullptr) {
        auto parentProperties = getClassScopeContainer(parent_id);

        if (isDeclaredConst(node->id, parentProperties->consts) || isPredeclaredConst(node->id))
            cout << "Warning: Constant " << *node->id << " already defined in " << *file_name << endl;
        else parentProperties->consts.push_back(node);

    } else {
        if (isDeclaredConst(node->id, consts) || isPredeclaredConst(node->id))
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
    } else interfaces.push_back(node);

    inspectInterfaceDef(node->expr_definition);

    if (node->stmt_list == nullptr) return;

    for (auto i: node->stmt_list->vector) {
        inspectInterfaceStmt(i, node->expr_definition->id);
    }

}

void inspectInterfaceDef(InterfaceExprDefNode *node) {
    if (node == nullptr) return;

    auto interfaceProps = getClassScopeContainer(node->id);

    string *prevId;

    if (node->id_extended_list != nullptr) {

        for (auto i: node->id_extended_list->vector) {
            if (!isDeclaredInterface(i, interfaces)) {
                if (isDeclaredClass(i, classes) ||
                    isDeclaredTrait(i))
                    throw runtime_error(string("Fatal error: " + *node->id + " cannot implement " +
                                               *i + " - it is not an interface in " +
                                               *file_name));
            } else {
                if (interfaceProps == nullptr) throw length_error("null error");
                interfaceProps->included.push_back(i); // Добавляю id найденного интерфейса в список includes
            }

            // Проверяю на дубликат в списке интерфейсов
            if (prevId != nullptr && *i == *prevId)
                throw runtime_error(
                        string("Fatal error: Interface " + *node->id +
                               " cannot implement previously implemented interface " + *i +
                               " in " + *file_name));
            else prevId = i;
        }
    }
}

void inspectInterfaceStmt(InterfaceStmtNode *node, string *parentId) {
    if (node == nullptr) return;

    if (node->access_mod != nullptr) {
        inspectClassAccessModList(node->access_mod);

        for (auto &i: node->access_mod->vector) {
            switch (i->access_mod) {
                case abstract_node:
                    throw runtime_error(
                            string("Fatal error: Interface method " + *parentId + "::" + *node->function_def->func_id +
                                   "() must not be abstract in " + *file_name));
                case final_node:
                    throw runtime_error(
                            string("Fatal error: Interface method " + *parentId + "::" + *node->function_def->func_id +
                                   "() must not be final in " + *file_name));
                case read_only_node:
                    throw runtime_error(
                            string("Fatal error: Cannot use 'readonly' as method modifier in " + *file_name));
            }
        }

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
    } else traits.push_back(node);

    if (node->stmt_list == nullptr) return;

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
            if (node->const_decl == nullptr) break;
            for (auto i: node->const_decl->vector) {
                inspectConstDecl(i);
            }
            break;
        case StmtType::continue_stmt:
            if (context != ContextType::inLoop && context != ContextType::inSwitch)
                throw runtime_error(
                        string("Fatal error: 'continue' not in the 'loop' or 'switch' context in " + *file_name));
            break;
        case StmtType::global_var:
            if (node->global_var == nullptr) break;
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
            if (node->static_var == nullptr) break;
            for (auto i: node->static_var->vector) {
                inspectStaticVar(i, variablesScope, constsScope, functionsScope, isInClass, context);
            }
            break;
        case StmtType::stmt_list:
            if (node->stmtList == nullptr) break;
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

    node->expr = ExprNode::CreateFromBoolCast(node->expr);

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
            if (node->stmtListMain == nullptr) break;
            for (auto i: node->stmtListMain->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope,
                            isInClass, ContextType::inIf);
            }
            break;
        case IfStmtType::if_else_endif:
            if (node->stmtListMain != nullptr) {
                for (auto i: node->stmtListMain->vector) {
                    inspectStmt(i, variablesScope, constsScope, functionsScope,
                                isInClass, ContextType::inIf);
                }
            }

            if (node->stmtListElse != nullptr) {
                for (auto i: node->stmtListElse->vector) {
                    inspectStmt(i, variablesScope, constsScope, functionsScope,
                                isInClass, ContextType::inIf);
                }
            }
            break;
        case IfStmtType::if_else_list_endif:
            if (node->stmtListMain != nullptr) {
                for (auto i: node->stmtListMain->vector) {
                    inspectStmt(i, variablesScope, constsScope, functionsScope,
                                isInClass, ContextType::inIf);
                }
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
    auto tmp = node->expr;
    node->expr->exprType = int_cast;
    node->expr->left = tmp;

    switch (node->type) {
        case SwitchStmtType::just_switch:
            break;
        case SwitchStmtType::switch_default:
            if (node->defaultStmtList == nullptr) break;
            for (auto i: node->defaultStmtList->vector) {
                inspectCaseDefaultStmt(i, variablesScope, constsScope, functionsScope, isInClass,
                                       ContextType::inSwitch);
            }
            break;
        case SwitchStmtType::switch_default_endswitch:
            if (node->defaultStmtList == nullptr) break;
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

    if (node->stmtList != nullptr) {
        for (auto i: node->stmtList->vector) {
            inspectStmt(i, variablesScope, constsScope, functionsScope, isInClass, ContextType::inSwitch);
        }
    }

    ExprNode *tmp;

    switch (node->type) {
        case CaseDefaultType::case_stmt:
            inspectExpr(node->expr, variablesScope, constsScope, functionsScope, isInClass, context);
            tmp = node->expr;
            node->expr->exprType = int_cast;
            node->expr->left = tmp;
            break;
        case CaseDefaultType::default_stmt:
        case CaseDefaultType::finally_stmt:
            break;
    }

}


//For statement
void inspectForStmt(ForStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                    vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    inspectExpr(node->expr_left, variablesScope, constsScope, functionsScope, isInClass, context);

    //Убрал доп массив, потому что не нужен, думал, что как в си, переменные внутри цикла снаружи быть не могут, а они глобальные


    node->expr_central = ExprNode::CreateFromBoolCast(node->expr_central);

    inspectExpr(node->expr_central, variablesScope, constsScope, functionsScope, isInClass, context);

    inspectExpr(node->expr_right, variablesScope, constsScope, functionsScope, isInClass, context);

    switch (node->type) {
        case ForStmtType::for_stmt_type:
            inspectStmt(node->stmt, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            break;
        case ForStmtType::for_end_stmt_type:
            if (node->stmtList == nullptr) break;
            for (auto i: node->stmtList->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            }
            break;
    }
}


//For each statement
void inspectForEachStmt(ForEachStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                        vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    inspectExpr(node->expr_left, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
    auto tmp = node->expr_left;

    node->expr_left->exprType = array_cast;
    node->expr_left->left = tmp;

    inspectExpr(node->expr_right, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);

    //Убрал доп массив, потому что не нужен, думал, что как в си, переменные внутри цикла снаружи быть не могут, а они могут

    switch (node->type) {
        case ForEachStmtType::foreach_stmt_type:
            inspectStmt(node->stmt, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            break;
        case ForEachStmtType::foreach_r_double_arrow_stmt_type:
        case ForEachStmtType::foreach_r_double_arrow_pointer_stmt_type:
            variablesScope.push_back(node->id);
            inspectStmt(node->stmt, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            break;
        case ForEachStmtType::end_foreach_stmt_type:
            if (node->stmtList == nullptr) break;
            for (auto i: node->stmtList->vector) {
                inspectStmt(node->stmt, variablesScope, constsScope, functionsScope, isInClass,
                            ContextType::inLoop);
            }
            break;
        case ForEachStmtType::end_foreach_r_double_arrow_stmt_type:
            variablesScope.push_back(node->id);

            if (node->stmtList == nullptr) break;
            for (auto i: node->stmtList->vector) {
                inspectStmt(node->stmt, variablesScope, constsScope, functionsScope, isInClass,
                            ContextType::inLoop);
            }
            break;
        case ForEachStmtType::end_foreach_r_double_arrow_pointer_stmt_type:
            variablesScope.push_back(node->id);

            if (node->stmtList == nullptr) break;
            for (auto i: node->stmtList->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            }
            break;
    }
}


// While statement
void inspectWhileStmt(WhileStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                      vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    node->expr = ExprNode::CreateFromBoolCast(node->expr);

    inspectExpr(node->expr, variablesScope, constsScope, functionsScope, isInClass, context);

    switch (node->type) {
        case WhileStmtType::while_stmt_type:
            inspectStmt(node->stmt, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            break;
        case WhileStmtType::end_while_stmt_type:

            if (node->stmtList == nullptr) break;
            for (auto i: node->stmtList->vector) {
                inspectStmt(i, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
            }
            break;
    }
}

void inspectDoWhileStmt(DoWhileStmtNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                        vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    node->expr = ExprNode::CreateFromBoolCast(node->expr);

    inspectExpr(node->expr, variablesScope, constsScope, functionsScope, isInClass, context);

    inspectStmt(node->stmt, variablesScope, constsScope, functionsScope, isInClass, ContextType::inLoop);
}


// Static variables
void inspectStaticVar(StaticVarNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                      vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    if (!isDeclaredVariable(node->id, variables)) {
        variables.push_back(node->id);
    }

    switch (node->type) {
        case StaticVarType::var:
            break;
        case StaticVarType::var_assign:
            inspectExpr(node->expr, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
    }
}


// Global variables
void inspectGlobalVar(GlobalVarNode *node, vector<string *> &variablesScope, vector<ConstDeclNode *> &constsScope,
                      vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    if (!isDeclaredVariable(node->id, variables)) {
        variables.push_back(node->id);
    }

}

//Expression
void inspectExpr(ExprNode *node, vector<string *> &variablesScope, const vector<ConstDeclNode *> &constsScope,
                 vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;
    ClassScopeContainer *parentScope;

    switch (node->exprType) {
        case ExprType::class_method_ref_op:
        case ExprType::class_method_by_ref_op:
        case ExprType::class_inst_field_by_expr_ref:
        case ExprType::class_inst_field_ref_op:
        case ExprType::class_inst_field_by_ref_op:
            inspectExpr(node->left, variablesScope, constsScope, functionsScope,
                        isInClass, ContextType::classInstRef);
            break;
        case ExprType::class_inst_field_ref_dots_op:
        case ExprType::class_inst_field_by_expr_ref_dots_op:
        case ExprType::class_inst_field_by_ref_dots_op:
            inspectExpr(node->left, variablesScope, constsScope, functionsScope,
                        isInClass, ContextType::staticRef);
            if (node->left == nullptr) return;
            break;
        case ExprType::class_inst_get_value_method_by_ref_op_dots:
            inspectExpr(node->left, variablesScope, constsScope, functionsScope,
                        isInClass, ContextType::staticRef);
            if (node->left == nullptr) return;
            break;
        case ExprType::this_keyword:
            if (!isInClass)
                throw runtime_error(
                        "Fatal error: Uncaught error: Using $this when in not in object context in " + *file_name);
        case ExprType::self_keyword:
            if (context == ContextType::staticRef && !currentObjectName.empty()) {
                node->exprType = ExprType::id_type;
                node->id = new string(currentObjectName);
            }
            break;
        case ExprType::assign_op:
        case ExprType::assign_ref_op:
            if (*node->left->id == "this" && node->get_value != nullptr && node->get_value->count == 1)
                //Throw fatal error
                throw runtime_error(string("Fatal error: Cannot re-assign $this in " + *file_name));
            //if use right-side variable is not declared
            if (node->right->exprType == ExprType::variable && !isDeclaredVariable(node->right->id, variables)) {
                node->right = ExprNode::CreateFromAssignOp(node->right, ExprNode::CreateFromNull());
                variables.push_back(node->right->left->id);
            } else {
                auto tmp = node->left;

                switch (node->left->exprType) {

                    case ExprType::get_array_val:
                        node->exprType = set_array_val;
                        node->left = tmp->left;
                        node->central = tmp->right;
                        inspectExpr(node->central, variablesScope, constsScope, functionsScope, isInClass, context);
                        break;

                    case ExprType::class_inst_field_ref_op:
                    case ExprType::class_field_ref_op:
                        node->exprType = set_class_field_op;
                        node->left = tmp->left;
                        node->id = tmp->id;
                        break;
                }

                delete tmp;
            }
        case ExprType::plus_op:
        case ExprType::minus_op:
        case ExprType::mult_op:
        case ExprType::div_op:
        case ExprType::mod_op:
        case ExprType::pow_op:
        case ExprType::instance_of:
        case ExprType::concat_op:
        case ExprType::bool_more:
        case ExprType::bool_less:
        case ExprType::bool_and:
        case ExprType::bool_equal:
        case ExprType::bool_or:
        case ExprType::bool_equal_strict:
        case ExprType::bool_equal_more:
        case ExprType::bool_equal_less:
        case ExprType::logic_and:
        case ExprType::logic_or:
        case ExprType::logic_xor:
        case ExprType::call_func:
        case ExprType::new_decl_no_id:
            inspectExpr(node->left, variablesScope, constsScope, functionsScope, isInClass, context);
            inspectExpr(node->right, variablesScope, constsScope, functionsScope, isInClass, context);
            inspectExprList(node->listParams, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case ExprType::u_minus_op:
        case ExprType::u_plus_op:
        case ExprType::int_cast:
        case ExprType::float_cast:
        case ExprType::bool_cast:
        case ExprType::string_cast:
        case ExprType::array_cast:
        case ExprType::object_cast:
        case ExprType::bool_not:
        case ExprType::clone_op:
            inspectExpr(node->left, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case ExprType::ref_op:
            inspectExpr(node->right, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case ExprType::ternary_op:
            node->left = ExprNode::CreateFromBoolCast(node->left);
            inspectExpr(node->left, variablesScope, constsScope, functionsScope, isInClass, context);
            inspectExpr(node->central, variablesScope, constsScope, functionsScope, isInClass, context);
            inspectExpr(node->right, variablesScope, constsScope, functionsScope, isInClass, context);
            break;
        case ExprType::id_type:
        case ExprType::new_decl:
        case ExprType::variable:
            if (!isDeclaredVariable(node->id, variables) && !isDeclaredVariable(node->id, variablesScope)) {
                switch (context) {
                    case ContextType::inFunction:
                        variablesScope.push_back(node->id);
                        break;
                    default:
                        variables.push_back(node->id);
                        break;
                }

            }
            break;

    }
}

void inspectExprList(ExprList *node, vector<string *> &variablesScope, const vector<ConstDeclNode *> &constsScope,
                     vector<FunctionStmtDeclNode *> &functionsScope, bool isInClass, ContextType context) {
    if (node == nullptr) return;

    for (auto tmp: node->vector) {
        inspectExpr(tmp, variablesScope, constsScope, functionsScope, isInClass, context);
    }
}
