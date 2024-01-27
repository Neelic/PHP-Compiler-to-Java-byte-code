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
    ConstantValue *name;
    int maxStack;
    int maxLocals;
    vector<ValueAndBytes *> *code;
//    vector<TableAttribute *> attributes; // TODO: Нормально бы удалить TableAttribute
    vector<ConstantValue *> *consts;
    vector<string *> params; // Список id локальных переменных

    int getAttrLength() {
        int res = 12; //exclude first 6 bytes
        res += getCodeLength();
//        for (auto table: attributes) {
//            res += table->getAttributeLength();
//        }

        return res;
    }

    int getCodeLength() {
        int res = 0;
        for (auto bytes: *code) {
            res += bytes->getBytes();
        }

        return res;
    }

public:
    CodeAttribute(int maxStack, int maxLocals, vector<ValueAndBytes *> *code, vector<ConstantValue *> *consts,
                  vector<string *> &params)
            : maxStack(maxStack), maxLocals(maxLocals), code(code), consts(consts), params(params) {
        auto nameStr = string("Code");
        name = ConstantValue::CreateUtf8(&nameStr, consts);
    }

    void addCodeValueByte(ValueAndBytes *value) {
        code->push_back(value);
    }

    vector<ValueAndBytes *> attributeToBytes() {
        auto res = vector<ValueAndBytes *>();

        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *name), 2));
        res.push_back(new ValueAndBytes(getAttrLength(), 4));
        res.push_back(new ValueAndBytes(maxStack, 2));
        res.push_back(new ValueAndBytes(maxLocals, 2));

        res.push_back(new ValueAndBytes(getCodeLength(), 4));
        res.insert(res.end(), code->begin(), code->end());
        res.push_back(new ValueAndBytes((int) 0, 2));

//        res.push_back(new ValueAndBytes((int) attributes.size(), 2));
//        for (auto table: attributes) {
//            auto tableBytes = table->attributeToBytes();
//            res.insert(res.end(), tableBytes.begin(), tableBytes.end());
//        }

        return res;
    }

    static CodeAttribute *
    fromStmtList(StmtList *node, int maxLocals, vector<string *> &params, vector<ConstantValue *> *consts) {
        if (node == nullptr) return nullptr;
        CodeAttribute *res;

        auto code_res = vector<ValueAndBytes *>();

        int byteCount = 0;

        res = new CodeAttribute(
                (int) 10,
                1000,
                &code_res,
                consts,
                params
        ); // TODO:  Какого черта он не создается



        for (auto i: params) {
            Commands::doCommandTwoBytes(_new,)
        }

        for (auto i: node->vector) {
            res->getCodeFromStmtNode(i, 0);
        }
    }

    vector<ValueAndBytes *> getCodeFromStmtNode(StmtNode *node, int currLine, int skipBytes = 0) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes *>();
        auto code_tmp = vector<ValueAndBytes *>();

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
                if (skipBytes > 0)
                    skipBytes + 3;
                Commands::doCommandTwoBytes(go_to, skipBytes, &res);
                break;
            case continue_stmt:
                //getCodeFromContinue
                break;
            case if_stmt:
                code_tmp = getCodeFromIfStmt(node->if_stmt, currLine);
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case switch_stmt:
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
                    getCodeFromExpr(node->expr_left, currLine, 1);
                    Commands::doCommand(areturn, &res);
                }
                break;
            default:
                break;
        }

        // Записываю код в code
        code->insert(code->end(), res.begin(), res.end());

        return res;
    }

    vector<ValueAndBytes *> getCodeFromIfStmt(IfStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes *>();
        auto main_code = vector<ValueAndBytes *>();
        auto else_code = vector<ValueAndBytes *>();
        auto code_tmp = vector<ValueAndBytes *>();

        int byteCount = currLine;
        int skipBytes = 0;

        switch (node->type) {

            case only_if:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true, при переходе вперед нужно добавлять размер самого сравнения, то бишь 3
                code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Нахожу код тела
                code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                //Считаю размер тела в байтах
                skipBytes += countByteSize(code_tmp);
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3, &res);
                //Записываю код тела в результат (тело сейчас в code_tmp)
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case if_else:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
                // Считаю, сколько строк было в подготовке условия
                byteCount += countByteSize(code_tmp);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Получаю байт код тела
                code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                //Считаю размер тела в байтах, +3 с учетом команды goto для пропуска else
                skipBytes = countByteSize(code_tmp) + 3;
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3, &res);
                //Записываю код тела в результат (тело сейчас в code_tmp)
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                //Получаю байт код блока else
                code_tmp = getCodeFromStmtNode(node->stmt_else, byteCount);
                //Считаю размер блока else
                skipBytes = countByteSize(code_tmp);
                //Записываю в конец главного блока комманду goto со сдвигом на размер else
                Commands::doCommandTwoBytes(go_to, skipBytes + 3, &res);
                //Записываю в результат блок else
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case end_if:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Нахожу код тела
                for (auto i: node->stmtListMain->vector) {
                    code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                    main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
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
                code_tmp = getCodeFromExpr(node->expr, byteCount + 3, 1);
                // Считаю, сколько строк было в подготовке условия
                byteCount += countByteSize(code_tmp);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Получаю байт код тела
                for (auto i: node->stmtListMain->vector) {
                    code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                    main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
                }
                //Считаю размер тела в байтах, +3 с учетом команды goto для пропуска else
                skipBytes += countByteSize(main_code) + 3;
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3, &res);
                //Записываю код тела в результат (тело сейчас в main_code)
                res.insert(res.end(), main_code.begin(), main_code.end());
                //Получаю байт код блока else
                for (auto i: node->stmtListElse->vector) {
                    code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                    else_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
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
                code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Нахожу код тела
                for (auto i: node->stmtListMain->vector) {
                    code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount);
                    main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
                }
                //Считаю размер тела в байтах с учетом goto для выхода из конструкции
                skipBytes = countByteSize(main_code) + 3;
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes + 3, &res);
                //Записываю код тела в результат (тело сейчас в main_code)
                res.insert(res.end(), main_code.begin(), main_code.end());
                //Получаю код всех else if
                for (auto i: node->listElse->vector) {
                    code_tmp = getCodeFromIfStmt(i, byteCount);
                    else_code.insert(else_code.end(), code_tmp.begin(), code_tmp.end());
                    skipBytes = countByteSize(else_code);
                    // Записываю в конец else if команду для перехода на строчку прямо перед конструкцией
                    Commands::doCommandTwoBytes(go_to, -skipBytes, &else_code);
                }
                skipBytes = countByteSize(else_code); // Здесь в else_code - весь блок else if
                Commands::doCommandTwoBytes(go_to, skipBytes + 3, &res); // Записываю сразу после main тела
                res.insert(res.end(), code_tmp.begin(), code_tmp.end()); // Записываю в результат блок else if
                break;
        }

        return res;
    }

    vector<ValueAndBytes *> getCodeFromWhileStmt(WhileStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes *>();
        auto main_code = vector<ValueAndBytes *>();
        auto code_tmp = vector<ValueAndBytes *>();

        int byteCount = currLine;
        int skipBytes = 0;

        // Условие продолжения цикла
        code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
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
        Commands::doCommandTwoBytes(go_to, -skipBytes, &res);// Переход к условию цикла

        return res;
    }

    vector<ValueAndBytes *> getCodeFromDoWhileStmt(DoWhileStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes *>();
        auto main_code = vector<ValueAndBytes *>();
        auto code_tmp = vector<ValueAndBytes *>();

        int byteCount = currLine;
        int skipBytes = 0;

        // Тело цикла
        main_code = getCodeFromStmtNode(node->stmt, byteCount);
        res.insert(res.end(), main_code.begin(), main_code.end()); // Тело while

        // Вычисление Условия продолжения цикла
        code_tmp = getCodeFromExpr(node->expr, byteCount, 1);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        // Получение размера условия с учетом вычисления условия продолжения цикла
        skipBytes = countByteSize(res);

        // Записываем условие: при выполнении условия, возвращает в начало цикла. Иначе, продолжает код
        Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifne, -skipBytes, res);

        return res;

    }

    vector<ValueAndBytes *> getCodeFromForStmt(ForStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes *>();
        auto main_code = vector<ValueAndBytes *>();
        auto code_tmp = vector<ValueAndBytes *>();

        int byteCount = currLine;
        int skipBytes = 0;

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

        skipBytes = countByteSize(main_code);
        //Записываем безусловный переход при старте for
        Commands::doCommandTwoBytes(go_to, skipBytes + 3, &res);

        // Записываем тело цикла
        res.insert(res.end(), main_code.begin(), main_code.end());

        // Записываем вычисление условия из центрального выражения for
        code_tmp = getCodeFromExpr(node->expr_central, currLine, 1);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
        skipBytes = countByteSize(main_code);

        // Проверка условия, если выполняется - продолжаем, иначе заканчиваем
        Commands::doCommandTwoBytes(ifne, -skipBytes, &res);

        return res;
    }

    vector<ValueAndBytes *> getCodeFromForeachStmt(ForEachStmtNode *node, int currLine) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes *>();
        auto main_code = vector<ValueAndBytes *>();
        auto code_tmp = vector<ValueAndBytes *>();

        int byteCount = currLine;
        int skipBytes = 0;

        auto loopIndex = new string(); // Хранит имя переменной, служащей индексом для обхода массива
        auto arrayItem = new string(); //Хранит имя переменной для текущего элемента массива

        // Записываем первое выражение из for
        code_tmp = getCodeFromExpr(node->expr_left, currLine, 0);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        // Записываем второе выражение из for
        code_tmp = getCodeFromExpr(node->expr_right, currLine, 0);
        res.insert(res.end(), code_tmp.begin(), code_tmp.end());

        if (node->id != nullptr) {
            //Создаю последнюю переменную в заголовке, если ее еще нет
            initializeNewVariable(node->id, &res);

            *loopIndex = *node->expr_right->id;
            *arrayItem = *node->id;

            // Подготавливаю индекс для обхода массива и обращения к значениям
            Commands::doCommand(iconst_0, &res);

            Commands::doCommand(istore, findParamId(node->expr_right->id), &res);

        } else {
            // Подготавливаю индекс для обхода массива и обращения к значениям
            auto loopIndexTemp = new string("loopIndex");
            initializeNewVariable(loopIndex, &res);

            Commands::doCommand(iconst_0, &res);
            Commands::doCommand(istore, findParamId(loopIndex), &res);

            *loopIndex = *loopIndexTemp;
            *arrayItem = *node->expr_right->id;
            delete loopIndexTemp;
        }

        // В начале цикла получаем текущий элемент массива
        // Записываю в стек ссылку на массив и индекс элемента
        Commands::doCommand(aload, findParamId(node->expr_left->id), &main_code);
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
        Commands::doCommand(aload, findParamId(node->expr_left->id), &main_code);
        Commands::doCommand(arraylength, &res); // Получаю размер массива

        Commands::doCommand(iload, findParamId(loopIndex), &main_code); // Получаю текущий индекс массива

        // Записываем тело цикла с условием
        res.insert(res.end(), main_code.begin(), main_code.end());

        // Проверка условия ( i<array.size), если выполняется - переходим к началу цикла, иначе заканчиваем
        Commands::doCommandTwoBytes(if_cmpgt, -skipBytes, &res);

        return res;

    }

    vector<ValueAndBytes *> getCodeFromExpr(ExprNode *node, int currLine, int toStack) {
        vector<ValueAndBytes *> res;
        if (node == nullptr) return res;

        vector<ValueAndBytes *> tmpVec;
        ConstantValue *tmpConstant1;
        ConstantValue *tmpConstant2;

        switch (node->exprType) {
            case int_val:
                Commands::doCommandTwoBytes(name_new, -1, &res); //TODO id class constant Value
                Commands::doCommand(dup, &res);
                tmpConstant1 = ConstantValue::CreateInteger(node->int_val, consts);
                Commands::doCommand(ldc, ConstantValue::getIdConst(consts, *tmpConstant1), &res);
                Commands::doCommandTwoBytes(invokespecial, -1, &res); //TODO id method ref Value(int)
                Commands::doCommand(astore, -1, &res); //TODO number of local variable
                break;
            case float_val:
                Commands::doCommandTwoBytes(name_new, -1, &res); //TODO id class constant Value
                Commands::doCommand(dup, &res);
                tmpConstant1 = ConstantValue::CreateFloat(node->float_val, consts); //copy pointer
                Commands::doCommand(ldc, ConstantValue::getIdConst(consts, *tmpConstant1), &res);
                Commands::doCommandTwoBytes(invokespecial, -1, &res); //TODO id method ref Value(float)
                Commands::doCommand(astore, -1, &res); //TODO number of local variable
                break;
            case string_val:
                Commands::doCommandTwoBytes(name_new, -1, &res); //TODO id class constant Value
                Commands::doCommand(dup, &res);
                if (ConstantValue::getIdConstByString(consts, node->string_val) == -1)
                    tmpConstant1 = ConstantValue::CreateString(
                            ConstantValue::CreateUtf8(node->string_val, consts),
                            consts);
                else
                    tmpConstant1 = ConstantValue::CreateString(
                            ConstantValue::getConstantByString(consts, node->string_val),
                            consts);
                //TODO Сделать проверку на существование string constant и для инта и флоата
                Commands::doCommand(ldc, ConstantValue::getIdConst(consts, *tmpConstant1), &res);
                Commands::doCommandTwoBytes(invokespecial, -1, &res); //TODO id method ref Value(String)
                Commands::doCommand(astore, -1, &res); //TODO number of local variable
                break;
                /// Assign
            case assign_op:
                //get on stack right part
                tmpVec = getCodeFromExpr(node->right, currLine, toStack);
                res.insert(res.end(), tmpVec.begin(), tmpVec.end());
                //op
                Commands::doCommand(astore, -1, &res); //TODO get id number of variable
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
                        ConstantValue::getIdConstByString(consts, new string("id_add"),
                                                          C_MethodRef), //TODO id на Value.add(Value)
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
                        ConstantValue::getIdConstByString(consts, new string("id_sub"),
                                                          C_MethodRef), //TODO id на Value.sub(Value)
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
                        ConstantValue::getIdConstByString(consts, new string("id_mul"),
                                                          C_MethodRef), //TODO id на Value.mul(Value)
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
                        ConstantValue::getIdConstByString(consts, new string("id_div"),
                                                          C_MethodRef), //TODO id на Value.div(Value)
                        &res
                );
                break;
                ///Local params
            case variable:
                //TODO aload № to bytes
                break;
            case id_type:
                //TODO const
                break;
        }

        return res; // Заглушка
    }

    static int countByteSize(vector<ValueAndBytes *> &code) {
        int res = 0;

        for (auto i: code) {
            res += i->getBytes();
        }

        return res;
    }

    int findParamId(string *value) {
        for (int i = 0; i < params.size(); i++) {
            if (*params[i] == *value)
                return i;
        }
        return -1;
    }

    void initializeNewVariable(string *varName, vector<ValueAndBytes *> *code_res) {

        if (varName == nullptr) return;

        auto classId = new string("RTL/Value;");
        auto constructor = new string("RTL/Value.()");

        auto arrayElementVar = findParamId(varName);

        if (arrayElementVar != -1) {
            return; // Если переменная уже есть
        }

        Commands::doCommandTwoBytes(_new,
                                    ConstantValue::getIdConstByString(consts, classId,
                                                                      ConstantType::C_Class),
                                    &code_res);

        Commands::doCommand(dup, &code_res);

        Commands::doCommand(iconst_0, &code_res); // Пока что Value будет создаваться от нуля

        Commands::doCommandTwoBytes(invokevirtual, ConstantValue::getIdConstByString(consts, constructor, C_MethodRef),
                                    &code_res);// Вызываю конструктор, по идее

        Commands::doCommand(astore, params.size(), &code_res); // Сохраняю ссылку на объект в новый параметр

        params.push_back(varName); // Сохраняю имя переменной в учете
    }

};

#endif //PHP_COMPILER_CODEATTRIBUTE_H
