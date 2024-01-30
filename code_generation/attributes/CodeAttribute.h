//
// Created by Dan on 23.01.2024.
//

#ifndef PHP_COMPILER_CODEATTRIBUTE_H
#define PHP_COMPILER_CODEATTRIBUTE_H


#include "code_generation/ConstantValue.h"
#include "code_generation/bytes/Commands.h"
#include "StmtList.hpp"
#include "StmtNode.hpp"
#include "StaticVarList.hpp"
#include "StaticVarNode.hpp"
#include "GlobalVarList.hpp"
#include "GlobalVarNode.hpp"
#include "parser_classes/Vector_classes/ConstDeclList/ConstDeclList.hpp"
#include "parser_classes/ConstDecl/ConstDeclNode.hpp"
#include "semantic/semantic.h"

class CodeAttribute {
private:
    ConstantValue name;
    int maxStack;
    int maxLocals;
    vector<ValueAndBytes> *code;
    vector<ConstantValue> *consts;
    vector<string> *params; // Список id локальных переменных

    int idClassConst = -1;

    int getAttrLength() const {
        int res = 12; //exclude first 6 bytes
        res += getCodeLength();
//        for (auto table: attributes) {
//            res += table->getAttributeLength();
//        }

        return res;
    }

    int getCodeLength() const {
        int res = 0;
        for (const auto &bytes: *code) {
            res += bytes.getBytes();
        }

        return res;
    }

public:
    CodeAttribute(int maxStack, int maxLocals, vector<ValueAndBytes> *code, vector<ConstantValue> *consts,
                  vector<string> *params)
            : maxStack(maxStack), maxLocals(maxLocals), code(code), consts(consts), params(params) {
        auto nameStr = string("Code");
        name = (ConstantValue::getIdConstByString(consts, "Code") == -1) ? ConstantValue::CreateUtf8(nameStr, consts) :
               ConstantValue::getConstantByString(consts, "Code");
    }

    void addCodeValueByte(ValueAndBytes &value) {
        code->push_back(value);
    }

    vector<ValueAndBytes> attributeToBytes() const {
        auto res = vector<ValueAndBytes>();
        //name id
        res.emplace_back(ConstantValue::getIdConst(consts, name), 2);
        //attribute len
        res.emplace_back(getAttrLength(), 4);
        //max stack
        res.emplace_back(maxStack, 2);
        //max locals
        res.emplace_back(maxLocals, 2);

        //code length
        res.emplace_back(getCodeLength(), 4);
        //code bytes
        res.insert(res.end(), code->begin(), code->end());

        //exception table count
        res.emplace_back((int) 0, 2);
        //code attributes count
        res.emplace_back((int) 0, 2);
//        for (auto table: attributes) {
//            auto tableBytes = table->attributeToBytes();
//            res.insert(res.end(), tableBytes.begin(), tableBytes.end());
//        }

        return res;
    }

    static const CodeAttribute *
    fromStmtList(StmtList *node, int maxLocals, vector<string> *params, vector<ConstantValue> *consts,
                 string returnType = "void") {
        if (node == nullptr) return nullptr;

        auto code_res = new vector<ValueAndBytes>();

        auto *res = new CodeAttribute(
                (int) 10,
                1000,
                code_res,
                consts,
                params
        );

        auto code_tmp = vector<ValueAndBytes>();

        for (auto i: *params) {
//            Commands::doCommandTwoBytes(_new,);
        }

        for (auto i: node->vector) {
            code_tmp = res->getCodeFromStmtNode(i, 0);
            res->code->insert(res->code->end(), code_tmp.begin(), code_tmp.end());
        }


        if (returnType == "void") {
            Commands::doCommand(_return, res->code);
        } else {
            Commands::doCommand(aconst_null, res->code);
            Commands::doCommand(areturn, res->code);
        }


        return res;
    }

    vector<ValueAndBytes> getCodeFromStmtNode(StmtNode *node, int currLine, int skipBytes = 0) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes>();
        auto code_tmp = vector<ValueAndBytes>();

        switch (node->type) {
            case stmt_list:
                for (auto i: node->stmtList->vector) {
                    code_tmp = getCodeFromStmtNode(i, currLine);
                    res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                }
                break;
            case expr:
                code_tmp = getCodeFromExpr(node->expr_left, currLine, 0);
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case break_stmt:
                if (skipBytes >= 0)
                    skipBytes + 3;
                Commands::doCommandTwoBytes(go_to, skipBytes, &res); // Заменяется на соответствующий переход
                break;
            case continue_stmt:
                if (skipBytes >= 0)
                    skipBytes + 3;
                Commands::doCommandTwoBytes(go_to, skipBytes, &res); // Заменяется на соответствующий переход
                break;
            case if_stmt:
                code_tmp = getCodeFromIfStmt(node->if_stmt, currLine);
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case switch_stmt:
                code_tmp = getCodeFromSwitchStmt(node->switch_stmt, currLine);
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case while_stmt:
                code_tmp = getCodeFromWhileStmt(node->while_stmt, currLine);
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case do_while_stmt:
                code_tmp = getCodeFromDoWhileStmt(node->do_while_stmt, currLine);
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case for_stmt:
                code_tmp = getCodeFromForStmt(node->for_stmt, currLine);
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case foreach_stmt:
                code_tmp = getCodeFromForeachStmt(node->foreach_stmt, currLine);
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case return_stmt:
                if (node->expr_left == nullptr) {
                    Commands::doCommand(_return, &res);
                } else {
                    code_tmp = getCodeFromExpr(node->expr_left, currLine, 1);
                    res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                    Commands::doCommand(areturn, &res);
                }
                break;
            case const_decl:
                for (auto i: node->const_decl->vector) {
                    initializeNewVariable(*i->id, &res, false);
                    //get on stack right part
                    code_tmp = getCodeFromExpr(i->expr, currLine, 1);
                    res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                    //op
                    Commands::doCommand(astore, findParamId(*i->id), &res);
                }
                break;
            case static_var:
                for (auto i: node->static_var->vector) {
                    initializeNewVariable(*i->id, &res, false);
                    //get on stack right part
                    code_tmp = getCodeFromExpr(i->expr, currLine, 1);
                    res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                    //op
                    Commands::doCommand(astore, findParamId(*i->id), &res);
                }
                break;
            case global_var:
                for (auto i: node->global_var->vector) {
                    initializeNewVariable(*i->id, &res);
                }
                break;
            case t_echo_stmt:
//                Commands::doCommandTwoBytes(_new, idClass("RTL/Functions"),
//                                            &res); // Создаю объект класса RTL/Functions

                code_tmp = getCodeFromExpr(node->expr_right, currLine, 1);// Нахожу параметр
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());

                Commands::doCommandTwoBytes(invokestatic, idMethodRef(
                        string("RTL/Functions"),
                        string("echo"),
                        string("(LRTL/Value;)V")), &res); // Выполняю функцию

                break;
        }

        return res;
    }

    vector<ValueAndBytes> getCodeFromIfStmt(IfStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes>();
        auto main_code = vector<ValueAndBytes>();
        auto else_code = vector<ValueAndBytes>();
        auto expr_code_tmp = vector<ValueAndBytes>();
        auto stmt_code_tmp = vector<ValueAndBytes>();

        int byteCount = currLine;
        int skipBytes = 0;

        switch (node->type) {

            case only_if:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true, при переходе вперед нужно добавлять размер самого сравнения, то бишь 3
                expr_code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
                convertBoolToInt(&expr_code_tmp);
                // Записываю подготовку условия в код
                res.insert(res.end(), expr_code_tmp.begin(), expr_code_tmp.end());
                // Нахожу код тела
                stmt_code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                //Считаю размер тела в байтах
                skipBytes += countByteSize(stmt_code_tmp);
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3, &res);
                //Записываю код тела в результат (тело сейчас в code_tmp)
                res.insert(res.end(), stmt_code_tmp.begin(), stmt_code_tmp.end());
                break;
            case if_else:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                expr_code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
                convertBoolToInt(&expr_code_tmp);
                // Считаю, сколько строк было в подготовке условия
                byteCount += countByteSize(expr_code_tmp);
                // Записываю подготовку условия в код
                res.insert(res.end(), expr_code_tmp.begin(), expr_code_tmp.end());
                // Получаю байт код тела
                stmt_code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                //Считаю размер тела в байтах, +3 с учетом команды goto для пропуска else
                skipBytes = countByteSize(stmt_code_tmp) + 3;
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3, &res);
                //Записываю код тела в результат (тело сейчас в code_tmp)
                res.insert(res.end(), stmt_code_tmp.begin(), stmt_code_tmp.end());
                //Получаю байт код блока else
                else_code = getCodeFromStmtNode(node->stmt_else, byteCount);
                //Считаю размер блока else
                skipBytes = countByteSize(else_code);
                //Записываю в конец главного блока комманду goto со сдвигом на размер else
                Commands::doCommandTwoBytes(go_to, skipBytes + 3, &res);
                //Записываю в результат блок else
                res.insert(res.end(), else_code.begin(), else_code.end());
                break;
            case end_if:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                expr_code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
                convertBoolToInt(&expr_code_tmp);
                // Записываю подготовку условия в код
                res.insert(res.end(), expr_code_tmp.begin(), expr_code_tmp.end());
                // Нахожу код тела
                for (auto i: node->stmtListMain->vector) {
                    stmt_code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                    main_code.insert(main_code.end(), stmt_code_tmp.begin(), stmt_code_tmp.end());
                }
                //Считаю размер тела в байтах
                skipBytes += countByteSize(main_code);
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3, &res);
                //Записываю код тела в результат (тело сейчас в main_code)
                res.insert(res.end(), main_code.begin(), main_code.end());
                break;
            case if_else_endif:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                expr_code_tmp = getCodeFromExpr(node->expr, byteCount + 3, 1);
                convertBoolToInt(&expr_code_tmp);
                // Считаю, сколько строк было в подготовке условия
                byteCount += countByteSize(expr_code_tmp);
                // Записываю подготовку условия в код
                res.insert(res.end(), expr_code_tmp.begin(), expr_code_tmp.end());
                // Получаю байт код тела
                for (auto i: node->stmtListMain->vector) {
                    stmt_code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                    main_code.insert(main_code.end(), stmt_code_tmp.begin(), stmt_code_tmp.end());
                }
                //Считаю размер тела в байтах, +3 с учетом команды goto для пропуска else
                skipBytes += countByteSize(main_code) + 3;
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3, &res);
                //Записываю код тела в результат (тело сейчас в main_code)
                res.insert(res.end(), main_code.begin(), main_code.end());
                //Получаю байт код блока else
                for (auto i: node->stmtListElse->vector) {
                    else_code = getCodeFromStmtNode(node->stmt_main, byteCount);
                    else_code.insert(main_code.end(), else_code.begin(), else_code.end());
                }
                //Считаю размер блока else
                skipBytes = countByteSize(else_code);
                //Записываю в конец главного блока комманду goto со сдвигом на размер else
                Commands::doCommandTwoBytes(go_to, skipBytes + 3, &res);
                //Записываю в результат блок else
                res.insert(res.end(), else_code.begin(), else_code.end());
                break;
            case if_else_list_endif:
                //Как выглядит схема в моей голове:
                // expr -> iconst_0 или iconst_1;
                // ifeq {размер тела плюс goto}
                //      {тело main}
                //      goto {размер всего else if}
                // {еще один if}
                //      {тело if main}
                //      goto -{размер всех предыдущих ifelse, чтобы попасть в ( goto {размер всего else if} ) }


                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                expr_code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
                convertBoolToInt(&expr_code_tmp);
                // Записываю подготовку условия в код
                res.insert(res.end(), expr_code_tmp.begin(), expr_code_tmp.end());
                // Нахожу код тела
                for (auto i: node->stmtListMain->vector) {
                    stmt_code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                    main_code.insert(main_code.end(), stmt_code_tmp.begin(), stmt_code_tmp.end());
                }
                //Считаю размер тела в байтах с учетом goto для выхода из конструкции
                skipBytes = countByteSize(main_code) + 3;
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3, &res);
                //Записываю код тела в результат (тело сейчас в main_code)
                res.insert(res.end(), main_code.begin(), main_code.end());
                //Получаю код всех else if
                for (auto i: node->listElse->vector) {
                    stmt_code_tmp = getCodeFromIfStmt(i, byteCount);
                    else_code.insert(else_code.end(), stmt_code_tmp.begin(), stmt_code_tmp.end());
                    skipBytes = countByteSize(else_code);
                    // Записываю в конец else if команду для перехода на строчку прямо перед конструкцией
                    Commands::doCommandTwoBytes(go_to, -skipBytes, &else_code);
                }
                skipBytes = countByteSize(else_code); // Здесь в else_code - весь блок else if
                Commands::doCommandTwoBytes(go_to, skipBytes + 3, &res); // Записываю сразу после main тела
                res.insert(res.end(), else_code.begin(), else_code.end()); // Записываю в результат блок else if
                break;
        }

        return res;
    }

    vector<ValueAndBytes> getCodeFromWhileStmt(WhileStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes>();
        auto main_code = vector<ValueAndBytes>();
        auto code_tmp = vector<ValueAndBytes>();

        int byteCount = currLine;
        int skipBytes = 0;

        if (node->stmtList != nullptr) {
            for (auto i: node->stmtList->vector) {
                findAllConstInStmtNode(i, &res);
            }
        }

        // Условие продолжения цикла
        code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
        convertBoolToInt(&code_tmp);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        // Тело цикла
        switch (node->type) {
            case while_stmt_type:
                // Тело цикла
                main_code = getCodeFromStmtNode(node->stmt, byteCount);
                break;
            case end_while_stmt_type:
                for (auto i: node->stmtList->vector) {
                    code_tmp = getCodeFromStmtNode(i, byteCount);
                    main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
                }
                break;
        }
        // +3, учитывая размер goto в конце тела
        skipBytes = countByteSize(main_code);

        Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3 + 3, &res);
        res.insert(res.end(), main_code.begin(), main_code.end()); // Тело while
        Commands::doCommandTwoBytes(go_to, -skipBytes - 3, &res);// Переход к условию цикла

        return res;
    }

    vector<ValueAndBytes> getCodeFromDoWhileStmt(DoWhileStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes>();
        auto main_code = vector<ValueAndBytes>();
        auto code_tmp = vector<ValueAndBytes>();

        int byteCount = currLine;
        int skipBytes = 0;

        if (node->stmt != nullptr) {
            findAllConstInStmtNode(node->stmt, &res);
        }

        // Тело цикла
        main_code = getCodeFromStmtNode(node->stmt, byteCount);
        res.insert(res.end(), main_code.begin(), main_code.end()); // Тело while

        // Вычисление Условия продолжения цикла
        code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
        convertBoolToInt(&code_tmp);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        // Получение размера условия с учетом вычисления условия продолжения цикла
        skipBytes = countByteSize(res);

        // Записываем условие: при выполнении условия, возвращает в начало цикла. Иначе, продолжает код
        Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifne, -skipBytes, &res);

        return res;

    }

    vector<ValueAndBytes> getCodeFromForStmt(ForStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes>();
        auto main_code = vector<ValueAndBytes>();
        auto code_tmp = vector<ValueAndBytes>();

        int byteCount = currLine;
        int skipBytes = 0;

        if (node->stmtList != nullptr) {
            for (auto i: node->stmtList->vector) {
                findAllConstInStmtNode(i, &res);
            }
        } else if (node->stmt != nullptr) {
            findAllConstInStmtNode(node->stmt, &res);
        }

        // Записываем первое выражение из for
        code_tmp = getCodeFromExpr(node->expr_left, currLine, 0);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        // Тело цикла
        switch (node->type) {
            case for_stmt_type:
                code_tmp = getCodeFromStmtNode(node->stmt, currLine);
                main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
                break;
            case for_end_stmt_type:
                for (auto i: node->stmtList->vector) {
                    code_tmp = getCodeFromStmtNode(i, currLine);
                    main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
                }
                break;
        }

        // Добавляем действие из последнего выражения for к телу цикла
        code_tmp = getCodeFromExpr(node->expr_right, currLine, 0);
        main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
        code_tmp = vector<ValueAndBytes>();

        skipBytes = countByteSize(main_code);
        //Записываем безусловный переход при старте for
        Commands::doCommandTwoBytes(go_to, skipBytes + 3, &res);

        // Записываем тело цикла
        res.insert(res.end(), main_code.begin(), main_code.end());

        // Записываем вычисление условия из центрального выражения for
        code_tmp = getCodeFromExpr(node->expr_central, currLine, 1);
        convertBoolToInt(&code_tmp);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
        skipBytes = countByteSize(main_code);

        // Проверка условия, если выполняется - продолжаем, иначе заканчиваем
        Commands::doCommandTwoBytes(ifne, -skipBytes, &res);

        return res;
    }

    // !!! В случае чего избегаем как чумы !!!
    vector<ValueAndBytes> getCodeFromForeachStmt(ForEachStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes>();
        auto main_code = vector<ValueAndBytes>();
        auto code_tmp = vector<ValueAndBytes>();

        int byteCount = currLine;
        int skipBytes = 0;

        auto loopIndex = string(); // Хранит имя переменной, служащей индексом для обхода массива
        auto arrayItem = string(); //Хранит имя переменной для текущего элемента массива

        // Записываем первое выражение из for
        code_tmp = getCodeFromExpr(node->expr_left, currLine, 0);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        // Записываем второе выражение из for
        code_tmp = getCodeFromExpr(node->expr_right, currLine, 0);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        // Если в заголовке есть параметр для ключа
        if (node->id != nullptr) {
            //Создаю последнюю переменную в заголовке, если ее еще нет
            initializeNewVariable(*node->id, &res);

            loopIndex = *node->expr_right->id;
            arrayItem = *node->id;

            // Подготавливаю индекс для обхода массива и обращения к значениям
            Commands::doCommand(iconst_0, &res);

            Commands::doCommand(istore, findParamId(*node->expr_right->id), &res);

        } else {
            // Подготавливаю индекс для обхода массива и обращения к значениям
            auto loopIndexTemp = string("loopIndex");
            initializeNewVariable(loopIndex, &res);

            Commands::doCommand(iconst_0, &res);
            Commands::doCommand(istore, findParamId(loopIndex), &res);

            loopIndex = loopIndexTemp;
            arrayItem = *node->expr_right->id;
        }

        // В начале цикла получаем текущий элемент массива
        // Записываю в стек ссылку на массив и индекс элемента
        Commands::doCommand(aload, findParamId(*node->expr_left->id), &main_code);
        Commands::doCommand(iload, findParamId(loopIndex), &main_code);
        //Загружаю элемент массива по индексу на стек и сохраняю в переменную текущего элемента массива
        Commands::doCommand(aaload, &main_code);
        Commands::doCommand(astore, findParamId(arrayItem), &main_code);

        // Тело цикла
        if (node->stmt != nullptr) {
            code_tmp = getCodeFromStmtNode(node->stmt, currLine);
            main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
        } else if (node->stmtList != nullptr) {
            for (auto i: node->stmtList->vector) {
                code_tmp = getCodeFromStmtNode(i, currLine);
                main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
            }
        }

        // Добавляем действие из последнего выражения for к телу цикла
        Commands::doCommand(iinc, findParamId(loopIndex), 1, &main_code);

        skipBytes = countByteSize(main_code);
        //Записываем безусловный переход при старте for к вычислению условия
        Commands::doCommandTwoBytes(go_to, skipBytes + 3, &res);

        // Добавляем в main_code вычисление условия из центрального выражения for
        Commands::doCommand(aload, findParamId(*node->expr_left->id), &main_code);
        Commands::doCommand(arraylength, &res); // Получаю размер массива

        Commands::doCommand(iload, findParamId(loopIndex), &main_code); // Получаю текущий индекс массива

        skipBytes = countByteSize(main_code);

        // Записываем тело цикла с условием
        res.insert(res.end(), main_code.begin(), main_code.end());

        // Проверка условия ( i<array.size), если выполняется - переходим к началу цикла, иначе заканчиваем
        Commands::doCommandTwoBytes(if_cmpgt, -skipBytes, &res);

        return res;

    }

    vector<ValueAndBytes> getCodeFromSwitchStmt(SwitchStmtNode *node, int currLine) {

        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes>();
        auto main_code = vector<ValueAndBytes>();
        auto code_tmp = vector<ValueAndBytes>();

        int byteCount = countByteSize(*code);
        int skipBytes = 3; // Сразу с учетом команды goto end;
        int defaultSkip = 0;
        auto skipList = vector<int>(); // Размер каждого блока case
        int ifSkip = 3; // Плюс команда goto для завершения

        // Приблизительная схема байт кода:
        //
        // вычисление cond1
        // if (ind = cond1) goto 1
        // вычисление сond2
        // if (ind = cond2) goto 2
        // goto default
        // (*) goto end
        // stmtlist 1
        // break -> goto *
        // stmtlist 2
        // break -> goto *
        // stmtlist default

        code_tmp = getCodeFromExpr(node->expr, currLine, 1);

        if (node->defaultStmtList == nullptr) return {};

        // Первый цикл - для получения тела и его размеров, а также размера каждого блока
        for (auto i: node->defaultStmtList->vector) {
            for (auto j: i->stmtList->vector) {
                if (j->type == break_stmt) {
                    code_tmp = getCodeFromStmtNode(j, currLine, -skipBytes);
                }
                code_tmp = getCodeFromStmtNode(j, currLine);
                skipBytes += countByteSize(code_tmp);
                main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());

            }
            switch (i->type) {
                case case_stmt:
                    skipList.push_back(countByteSize(main_code));
                    break;
                case default_stmt:
                    defaultSkip = countByteSize(main_code);
                    break;
                default:
                    break;
            }
        }
        // Второй цикл - узнать размер блоков if
        for (auto i: node->defaultStmtList->vector) {
            switch (i->type) {
                case case_stmt:
                    // Создаю узел Expr, чтобы кодген експра разбирался со сравнением. Именно тут просто оценивание размера блока в байтах для переходов, код в результат не записываю(пока)
                    code_tmp = getCodeFromExpr(
                            ExprNode::CreateFromBoolCast(ExprNode::CreateFromBooleanOpEqual(node->expr, i->expr)),
                            currLine, 0);
                    convertBoolToInt(&code_tmp);
                    ifSkip += countByteSize(code_tmp) + 3;// Потому что еще команда сравнения
                    break;
                case default_stmt:
                    ifSkip += 3; // здесь просто команда goto, поэтому 3
                    break;
                default:
                    break;
            }
        }

        // Третий цикл - наконец записать код

        int countCase = 0; // Порядковый номер блока case, нужен для получения значения из skipList

        for (auto i: node->defaultStmtList->vector) {
            switch (i->type) {
                case case_stmt:
                    code_tmp = getCodeFromExpr(
                            ExprNode::CreateFromBoolCast(ExprNode::CreateFromBooleanOpEqual(node->expr, i->expr)),
                            currLine, 0);
                    convertBoolToInt(&code_tmp);
                    res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                    ifSkip -= countByteSize(code_tmp); // Вычитаю, так как переход происходит после вычисления условия
                    Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifne, ifSkip + skipList[countCase], &res);
                    ifSkip -= 3; // Убираем размер команды условия
                    break;
                case default_stmt:
                    Commands::doCommandTwoBytes(go_to, ifSkip + defaultSkip, &res);
                    ifSkip -= 3; // Убираем размер команды перехода
                    break;
                default:
                    break;
            }
        }

        // Сам код всех case находится в main_code, записываем его
        res.insert(res.end(), main_code.begin(), main_code.end());

        return res;

    }

private:
    int idToStore = -1;
    bool isNeedToStore = false;

public:

    vector<ValueAndBytes> getCodeFromExpr(ExprNode *node, int currLine, int toStack) {
        vector<ValueAndBytes> res;
        if (node == nullptr) return res;
        int target;

        vector<ValueAndBytes> tmpVec;
        idClassConst = idClass(string("RTL/Value"));
        string isVar;
        int n = 0;

        switch (node->exprType) {
            case int_val:
                // create new value
                Commands::doCommandTwoBytes(_new, idClassConst, &res);
                Commands::doCommand(dup, &res);
                //if consts hasn't integer const
                if (ConstantValue::getIdConstByString(consts, string(to_string(node->int_val)), C_Integer) == -1)
                    ConstantValue::CreateInteger(node->int_val, consts);
                //load int to stack
                Commands::doCommand(ldc,
                                    ConstantValue::getIdConstByString(consts, string(to_string(node->int_val)),
                                                                      C_Integer),
                                    &res);
                Commands::doCommandTwoBytes(
                        invokespecial,
                        idMethodRef(
                                string("RTL/Value"),
                                string("<init>"),
                                string("(I)V")),
                        &res); //id на Value(int)
                break;
            case float_val:
                // create new value
                Commands::doCommandTwoBytes(_new, idClassConst, &res);
                Commands::doCommand(dup, &res);
                //if consts hasn't float const
                if (ConstantValue::getIdConstByString(consts, string(to_string(node->float_val)), C_Float) == -1)
                    ConstantValue::CreateFloat(node->float_val, consts); //copy pointer
                //load float to stack
                Commands::doCommand(ldc,
                                    ConstantValue::getIdConstByString(consts, to_string(node->float_val), C_Float),
                                    &res);
                Commands::doCommandTwoBytes(
                        invokespecial,
                        idMethodRef(
                                string("RTL/Value"),
                                string("<init>"),
                                string("(F)V")),
                        &res); //id на Value(float)
                break;
            case string_val:
                // create new value
                Commands::doCommandTwoBytes(_new, idClassConst, &res);
                Commands::doCommand(dup, &res);
                //if consts hasn't string const
                if (ConstantValue::getIdConstByString(consts, *node->string_val, C_String) == -1) {
                    if (ConstantValue::getIdConstByString(consts, *node->string_val) == -1)
                        ConstantValue::CreateUtf8(*node->string_val, consts);
                    ConstantValue::CreateString(
                            ConstantValue::getConstantByString(consts, *node->string_val),
                            consts);
                }
                //load string const
                Commands::doCommand(ldc, ConstantValue::getIdConstByString(consts, *node->string_val, C_String), &res);
                Commands::doCommandTwoBytes(
                        invokespecial,
                        idMethodRef(
                                string("RTL/Value"),
                                string("<init>"),
                                string("(Ljava/lang/String;)V")
                        ), &res); //id на Value(String)
                break;
                /// Assign
            case assign_op:
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, 1);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                if (node->left->exprType == variable) isVar = "$";
                if (findParamId(isVar + *node->left->id) == -1) params->emplace_back(isVar + *node->left->id);
                Commands::doCommand(astore, findParamId(isVar + *node->left->id), &res);
                break;
                ///Math ops
            case plus_op:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("add"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.add(Value)
                        &res
                );
                break;
            case minus_op:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("sub"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.sub(Value)
                        &res
                );
                break;
            case mult_op:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("mul"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.mul(Value)
                        &res
                );
                break;
            case div_op:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("div"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.div(Value)
                        &res
                );
                break;
            case pow_op:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("pow"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.pow(Value)
                        &res
                );
                break;
            case mod_op:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("div"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.mod(Value)
                        &res
                );
                break;
            case concat_op:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("concat"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.div(Value)
                        &res
                );
                break;
            case u_minus_op:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toFloatVal"),
                                string("()LRTL/Value;")
                        ), //id на Value.toFloatVal()
                        &res
                );
                Commands::doCommand(iconst_m1, &res);
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("mul"),
                                string("(I)LRTL/Value;")
                        ), //id на Value.toFloatVal()
                        &res
                );
                break;
            case u_plus_op:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toFloatVal"),
                                string("()LRTL/Value;")
                        ), //id на Value.toFloatVal()
                        &res
                );
                break;
                ///Logic ops
            case bool_equal:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("equals"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.equals(Value)
                        &res
                );
                break;
            case bool_equal_strict:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("equalsStrict"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.equalsStrict(Value)
                        &res
                );
                break;
            case bool_not:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("not"),
                                string("()LRTL/Value;")
                        ), //id на Value.not()
                        &res
                );
                break;
            case bool_more:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("more"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.more(Value)
                        &res
                );
                break;
            case bool_less:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("less"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.less(Value)
                        &res
                );
                break;
            case bool_and:
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack left part
                Commands::doCommandTwoBytes(invokevirtual,
                                            idMethodRef(
                                                    string("RTL/Value"),
                                                    string("toBoolVal"),
                                                    string("()LRTL/Value;")
                                            ), &res);
                Commands::doCommand(dup, &res);
                convertBoolToInt(&res);

                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("and"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.and(Value)
                        &tmpVec
                );

                Commands::doCommandTwoBytes(ifeq, countByteSize(tmpVec)+3, &res);

                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                break;
            case bool_or:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("or"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ), //id на Value.or(Value)
                        &res
                );
                break;
                ///Local params
            case variable:
                if (findParamId('$' + *node->id) == -1) {
                    params->emplace_back('$' + *node->id);
                    Commands::doCommandTwoBytes(_new, idClassConst, &res);
                    Commands::doCommand(dup, &res);
                    Commands::doCommandTwoBytes(
                            invokespecial,
                            idMethodRef(
                                    string("RTL/Value"),
                                    string("<init>"),
                                    string("()V")
                            ), &res); //id на Value(String)
                    Commands::doCommand(astore, findParamId(string('$' + *node->id)), &res);
                }
                Commands::doCommand(aload, findParamId('$' + *node->id), &res);
                if (isNeedToStore) idToStore = findParamId('$' + *node->id);
                break;
            case id_type:
                if (findParamId(*node->id) == -1) {
                    if (isPredConst(node->id)) {
                        setPredConstCode(*node->id, &res);
                    } else
                        throw runtime_error(
                                "Fatal Error: Undefined constant \"" +
                                *node->id + "\"");
                }
                Commands::doCommand(aload, findParamId(*node->id), &res);
                if (isNeedToStore) findParamId(*node->id);
                break;
                ///Array
            case set_array_val:
                isNeedToStore = true;
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //cast to array
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toArray"),
                                string("()LRTL/Value;")
                        ), //id на Value.toArrayVal()
                        &res
                );
                if (idToStore != -1) {
                    Commands::doCommand(astore, idToStore, &res);
                    Commands::doCommand(aload, idToStore, &res);
                    idToStore = -1;
                }
                //get on stack central part
                tmpVec = getCodeFromExpr(node->central, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("addToArray"),
                                string("(LRTL/Value;LRTL/Value;)V")
                        ),
                        &res
                );
                isNeedToStore = false;
                break;
            case add_array_val:
                isNeedToStore = true;
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //cast to array
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toArray"),
                                string("()LRTL/Value;")
                        ), //id на Value.toArray()
                        &res
                );
                if (idToStore != -1) {
                    Commands::doCommand(astore, idToStore, &res);
                    Commands::doCommand(aload, idToStore, &res);
                    idToStore = -1;
                }
                isNeedToStore = false;
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("addToArray"),
                                string("(LRTL/Value;)V")
                        ),
                        &res
                );
                break;
            case get_array_val:
                isNeedToStore = true;
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                isNeedToStore = false;
                //cast to array
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toArray"),
                                string("()LRTL/Value;")
                        ), //id на Value.toArray()
                        &res
                );
                if (idToStore != -1) {
                    Commands::doCommand(astore, idToStore, &res);
                    Commands::doCommand(aload, idToStore, &res);
                    idToStore = -1;
                }
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("getArrayVal"),
                                string("(LRTL/Value;)LRTL/Value;")
                        ),
                        &res
                );
                break;
                ///Casts
            case int_cast:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toIntVal"),
                                string("()LRTL/Value;")
                        ), //id на Value.toIntVal()
                        &res
                );
//                if (isNeedToStore && idToStore != -1) Commands::doCommand(astore, idToStore, &res);
                break;
            case float_cast:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toFloatVal"),
                                string("()LRTL/Value;")
                        ), //id на Value.toFloatVal()
                        &res
                );
//                if (isNeedToStore && idToStore != -1) Commands::doCommand(astore, idToStore, &res);
                break;
            case bool_cast:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toBoolVal"),
                                string("()LRTL/Value;")
                        ), //id на Value.toBoolVal()
                        &res
                );
//                if (isNeedToStore && idToStore != -1) Commands::doCommand(astore, idToStore, &res);
                break;
            case string_cast:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toStringVal"),
                                string("()LRTL/Value;")
                        ), //id на Value.toStringVal()
                        &res
                );
//                if (isNeedToStore && idToStore != -1) Commands::doCommand(astore, idToStore, &res);
                break;
            case array_cast:
                //get on stack left part
                tmpVec = getCodeFromExpr(node->left, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommandTwoBytes(
                        invokevirtual,
                        idMethodRef(
                                string("RTL/Value"),
                                string("toArray"),
                                string("()LRTL/Value;")
                        ), //id на Value.toArray()
                        &res
                );
                break;
                /// Function call
            case call_func:
                for (auto var: node->listParams->vector) {
                    tmpVec = getCodeFromExpr(var, currLine, toStack);
                    res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                    n++;
                }
                Commands::doCommandTwoBytes(
                        invokestatic,
                        idMethodRef(
                                string("_main"),
                                *node->id,
                                string("(" + repeatStr(n, "LRTL/Value;") + ")LRTL/Value;")
                        ),
                        &res
                );
                break;
            case t_readline:
                Commands::doCommandTwoBytes(invokestatic, idMethodRef(
                        string("RTL/Functions"),
                        string("readline"),
                        string("()LRTL/Value;")), &res); // Выполняю функцию
                break;
        }

        return res;
    }

    static bool isPredConst(string *id) {
        return *id == "true" || *id == "false" || *id == "null";
    }

    void setPredConstCode(const string &id, vector<ValueAndBytes> *res) {
        if (-1 != findParamId(id)) return;

        params->push_back(id);
        // cre->te new value
        Commands::doCommandTwoBytes(_new, idClassConst, res);
        Commands::doCommand(dup, res);

        if (id == "null") {
            Commands::doCommandTwoBytes(
                    invokespecial,
                    idMethodRef(
                            string("RTL/Value"),
                            string("<init>"),
                            string("()V")),
                    res); //id на Value()
        } else {
            if (id == "true") Commands::doCommand(iconst_1, res);
            else if (id == "false") Commands::doCommand(iconst_0, res);

            Commands::doCommandTwoBytes(
                    invokespecial,
                    idMethodRef(
                            string("RTL/Value"),
                            string("<init>"),
                            string("(Z)V")),
                    res); //id на Value(int)
        }

        Commands::doCommand(astore, findParamId(id), res);
    }

    static string repeatStr(int n, const string &str) {
        string res;
        for (int i = 0; i < n; i++) {
            res += str;
        }

        return res;
    }

    int idUtf8(const string &value) const {
        if (ConstantValue::getIdConstByString(consts, value) == -1)
            ConstantValue::CreateUtf8(value, consts);

        return ConstantValue::getIdConstByString(consts, value);
    }

    int idClass(const string &className) const {
        if (ConstantValue::getIdConstByString(consts, className, C_Class) == -1) {
            idUtf8(className);
            ConstantValue::CreateClass(
                    ConstantValue::getConstantByString(consts, className),
                    consts);
        }

        return ConstantValue::getIdConstByString(consts, className, C_Class);
    }

    int idMethodRef(const string &className, const string &nameMethod, const string &typeMethod) {
        idClass(className);

        if (ConstantValue::getIdConstByString(consts, string(nameMethod + typeMethod), C_NameAndType) == -1) {
            idUtf8(nameMethod);

            idUtf8(typeMethod);

            ConstantValue::CreateNameAndType(
                    ConstantValue::getConstantByString(consts, nameMethod),
                    ConstantValue::getConstantByString(consts, typeMethod),
                    consts
            );
        }

        if (ConstantValue::getIdConstByString(consts,
                                              string(className + '.' + nameMethod + typeMethod),
                                              C_MethodRef) == -1) {
            ConstantValue::CreateMethodRef(
                    ConstantValue::getConstantByString(consts, className, C_Class),
                    ConstantValue::getConstantByString(consts,
                                                       string(nameMethod + typeMethod),
                                                       C_NameAndType),
                    consts
            );
        }

        return ConstantValue::getIdConstByString(consts, string(className + '.' + nameMethod + typeMethod),
                                                 C_MethodRef);
    }

    static int countByteSize(vector<ValueAndBytes> &code) {
        int res = 0;

        for (const auto &i: code) {
            res += i.getBytes();
        }

        return res;
    }

    int findParamId(const string &value) const {
        for (int i = 0; i < params->size(); i++) {
            if ((*params)[i] == value)
                return i;
        }
        return -1;
    }

    void initializeNewVariable(const string &varName, vector<ValueAndBytes> *code_res, bool isVar = true) {
        auto classId = string("RTL/Value");
        auto constructor = string("RTL/Value.()V");

        idClassConst = idClass(string("RTL/Value"));

        if (!isVar && findParamId(varName) == -1) {
            params->emplace_back(varName);
            Commands::doCommandTwoBytes(_new, idClassConst, code_res);
            Commands::doCommand(dup, code_res);
            Commands::doCommandTwoBytes(
                    invokespecial,
                    idMethodRef(
                            string("RTL/Value"),
                            string("<init>"),
                            string("()V")
                    ), code_res); //id на Value(String)
            Commands::doCommand(astore, findParamId(string(varName)), code_res);
        }

        if (isVar && findParamId('$' + varName) == -1) {
            params->emplace_back('$' + varName);
            Commands::doCommandTwoBytes(_new, idClassConst, code_res);
            Commands::doCommand(dup, code_res);
            Commands::doCommandTwoBytes(
                    invokespecial,
                    idMethodRef(
                            string("RTL/Value"),
                            string("<init>"),
                            string("()V")
                    ), code_res); //id на Value(String)
            Commands::doCommand(astore, findParamId(string('$' + varName)), code_res);
        }
    }

    // Переводит Value(bool) в int, нужно для комманд сравнения. После выполнения в стеке должна лежать int 1 или 0
    void convertBoolToInt(vector<ValueAndBytes> *code_res) {

        //Приводит Value(bool) к Value(int)
        Commands::doCommandTwoBytes(invokevirtual,
                                    idMethodRef(string("RTL/Value"),
                                                string("toIntVal"),
                                                string("()LRTL/Value;")),
                                    code_res);
        //Получает int
        Commands::doCommandTwoBytes(invokevirtual,
                                    idMethodRef(string("RTL/Value"),
                                                string("getInt"),
                                                string("()I")),
                                    code_res);
    }

    void findAllConstInStmtNode(StmtNode *node, vector<ValueAndBytes> *code_res) {

        if (node == nullptr) return;

        auto res = vector<ConstantValue *>();

        switch (node->type) {
            case expr:
                findConstantInExpr(node->expr_left, code_res);
                break;
            case if_stmt:
                findAllConstantsInIfStmt(node->if_stmt, code_res);
                break;
            case switch_stmt:
                findAllConstantsInSwitchStmt(node->switch_stmt, code_res);
                break;
            case stmt_list:
                for (auto i: node->stmtList->vector)
                    findAllConstInStmtNode(i, code_res);
                break;
            case static_var:
                for (auto i: node->static_var->vector) {
                    if (i->id != nullptr) {
                        addConstant(*i->id, new string("LRTL/Value;"), code_res);
                    }
                }
                break;
            case global_var:
                for (auto i: node->global_var->vector) {
                    if (i->id != nullptr) {
                        addConstant(*i->id, new string("LRTL/Value;"), code_res);
                    }
                }
                break;
            case while_stmt:
                findConstsInWhileStmt(node->while_stmt, code_res);
                break;
            case do_while_stmt:
                findConstsInDoWhile(node->do_while_stmt, code_res);
                break;
            case for_stmt:
                findConstsInForStmt(node->for_stmt, code_res);
                break;
            case foreach_stmt:
                findConstsInForEachStmt(node->foreach_stmt, code_res);
                break;
            case const_decl:
                for (auto i: node->const_decl->vector) {
                    findConstsInConstDeclNode(i, code_res);
                }
                break;
        }
    }

    void findAllConstantsInIfStmt(IfStmtNode *node, vector<ValueAndBytes> *code_res) {
        if (node == nullptr) return;

        if (node->expr != nullptr)
            findConstantInExpr(node->expr, code_res);
        if (node->stmt_main != nullptr)
            findAllConstInStmtNode(node->stmt_main, code_res);
        if (node->stmt_else != nullptr)
            findAllConstInStmtNode(node->stmt_else, code_res);
        if (node->stmtListMain != nullptr) {
            for (auto i: node->stmtListMain->vector) {
                findAllConstInStmtNode(i, code_res);
            }
        }
        if (node->stmtListElse != nullptr) {
            for (auto i: node->stmtListElse->vector) {
                findAllConstInStmtNode(i, code_res);
            }
        }
        if (node->listElse != nullptr) {
            for (auto i: node->listElse->vector) {
                findAllConstantsInIfStmt(i, code_res);
            }
        }
    }

    void findAllConstantsInSwitchStmt(SwitchStmtNode *node, vector<ValueAndBytes> *code_res) {
        if (node == nullptr) return;

        if (node->expr != nullptr) {
            findConstantInExpr(node->expr, code_res);
        }

        if (node->defaultStmtList != nullptr) {
            for (auto i: node->defaultStmtList->vector) {
                if (i->expr != nullptr)
                    findConstantInExpr(i->expr, code_res);
                if (i->stmtList != nullptr) {
                    for (auto j: i->stmtList->vector) {
                        findAllConstInStmtNode(j, code_res);
                    }
                }
            }

        }
    }

    void findConstsInWhileStmt(WhileStmtNode *node, vector<ValueAndBytes> *code_res) {
        if (node == nullptr) return;

        if (node->expr != nullptr) {
            findConstantInExpr(node->expr, code_res);
        }

        switch (node->type) {
            case while_stmt_type:
                findAllConstInStmtNode(node->stmt, code_res);
                break;
            case end_while_stmt_type:
                for (auto i: node->stmtList->vector) {
                    findAllConstInStmtNode(i, code_res);
                }
                break;
        }
    }

    void findConstsInDoWhile(DoWhileStmtNode *node, vector<ValueAndBytes> *code_res) {
        if (node == nullptr) return;

        findConstantInExpr(node->expr, code_res);

        findAllConstInStmtNode(node->stmt, code_res);
    }

    void findConstsInForStmt(ForStmtNode *node, vector<ValueAndBytes> *code_res) {
        if (node == nullptr) return;

        findConstantInExpr(node->expr_left, code_res);

        switch (node->type) {

            case for_stmt_type:
                findAllConstInStmtNode(node->stmt, code_res);
                break;
            case for_end_stmt_type:
                for (auto i: node->stmtList->vector) {
                    findAllConstInStmtNode(node->stmt, code_res);
                }
                break;
        }

    }

    void findConstsInForEachStmt(ForEachStmtNode *node, vector<ValueAndBytes> *code_res) {
        if (node == nullptr) return;

        findConstantInExpr(node->expr_right, code_res);

        if (node->id != nullptr) {
            addConstant(*node->id, new string("LRTL/Value;"), code_res, false);
        }

        if (node->stmt != nullptr) {
            findAllConstInStmtNode(node->stmt, code_res);
        } else if (node->stmtList != nullptr) {
            for (auto i: node->stmtList->vector) {
                findAllConstInStmtNode(node->stmt, code_res);
            }
        }
    }

    void findConstsInConstDeclNode(ConstDeclNode *node, vector<ValueAndBytes> *code_res) {
        if (node == nullptr) return;
        addConstant(*node->id, new string("LRTL/Value;"), code_res, false);
    }

    void findConstantInExpr(ExprNode *node, vector<ValueAndBytes> *code_res) {
        if (node == nullptr) return;

        switch (node->exprType) {
            case assign_ref_op:
            case assign_op:
                findConstantInExpr(node->right, code_res);
                break;
            case variable:
                addConstant(*node->id, new string("LRTL/Value;"), code_res);
                break;
            case ExprType::u_minus_op:
            case ExprType::u_plus_op:
            case ExprType::int_cast:
            case clone_op:
            case float_cast:
            case string_cast:
            case array_cast:
            case object_cast:
            case bool_cast:
            case class_inst_field_ref_op:
            case class_inst_field_by_ref_op:
                findConstantInExpr(node->left, code_res);
                break;
            case class_inst_method_by_ref_op_dots:
                findConstantInExpr(node->left, code_res);
                break;
            case set_class_field_op:
                findConstantInExpr(node->right, code_res);
                break;
            case class_method_ref_op:
                findConstantInExpr(node->left, code_res);
                break;
            case class_inst_field_ref_dots_op:
                findConstantInExpr(node->left, code_res);
                break;
            case class_inst_field_by_ref_dots_op:
                findConstantInExpr(node->left, code_res);
                break;
            case instance_of:
                findConstantInExpr(node->left, code_res);
                break;
            case ExprType::plus_op:
            case ExprType::minus_op:
            case ExprType::mult_op:
            case ExprType::div_op:
            case ExprType::mod_op:
            case ExprType::pow_op:
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
                findConstantInExpr(node->left, code_res);
                findConstantInExpr(node->right, code_res);
                break;
            case ternary_op:
            case get_array_val:
            case add_array_val:
            case set_array_val:
                findConstantInExpr(node->left, code_res);
                findConstantInExpr(node->right, code_res);
                findConstantInExpr(node->central, code_res);
                break;
            case ref_op:
                findConstantInExpr(node->right, code_res);
            default:
                break;
        }
    }

    // Выделил в отдельную функцию, чтоб было не так больно исправлять
    void addConstant(const string &id, string *type, vector<ValueAndBytes> *code_res, bool isVar = true) {
        initializeNewVariable(id, code_res, isVar);
    }

};

#endif //PHP_COMPILER_CODEATTRIBUTE_H
