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
    CodeAttribute(int maxStack, int maxLocals, vector<ValueAndBytes *> *code, vector<ConstantValue *> *consts)
            : maxStack(maxStack), maxLocals(maxLocals), code(code), consts(consts) {
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
    fromStmtList(StmtList *node, int maxLocals, vector<ConstantValue *> &params, vector<ConstantValue *> &consts) {
        if (node == nullptr) return nullptr;
        CodeAttribute *res;

        auto code_res = vector<ValueAndBytes *>();
        auto code_tmp = vector<ValueAndBytes *>();

        int byteCount = 0;

        for (auto i: node->vector) {
            code_tmp = getCodeFromStmtNode(i, byteCount, consts);

            byteCount += countByteSize(code_tmp);

            code_res.insert(code_res.end(), code_tmp.begin(), code_tmp.end());
        }
    }

    static vector<ValueAndBytes *> getCodeFromStmtNode(StmtNode *node, int currLine, vector<ConstantValue *> &consts) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes *>();
        auto code_tmp = vector<ValueAndBytes *>();

        switch (node->type) {
                case StmtType::stmt_list:
                    for (auto i: node->stmtList->vector) {
                        code_tmp = getCodeFromStmtNode(i, currLine, consts);
                    }
                    break;
                case StmtType::expr:
                    //getCodeFromStmt
                    break;
                case StmtType::break_stmt:
                    //getCodeFromBreak;
                    break;
                case StmtType::continue_stmt:
                    //getCodeFromContinue
                    break;
                case StmtType::if_stmt:
                    //GenCodeFromIfStmt
                    break;
            case switch_stmt:
                break;
            case while_stmt:
                break;
            case do_while_stmt:
                break;
            case for_stmt:
                break;
            case foreach_stmt:
                break;
            case return_stmt:
                break;
            default:
                break;
            }

        res.insert(res.end(), code_tmp.begin(), code_tmp.end());
    }

    static vector<ValueAndBytes *> getCodeFromIfStmt(IfStmtNode *node, int currLine, vector<ConstantValue *> &consts) {
        if (node == nullptr) return {};

        auto res = vector<ValueAndBytes *>();
        auto main_code = vector<ValueAndBytes *>();
        auto else_code = vector<ValueAndBytes *>();
        auto code_tmp = vector<ValueAndBytes *>();

        int byteCount = currLine;
        int skipBytes = 0;

        switch (node->type) {

            case only_if:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                code_tmp = getCodeFromExpr(node->expr, byteCount, consts, ContextType::ifCondition);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Нахожу код тела
                code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount, consts);
                //Считаю размер тела в байтах
                skipBytes += countByteSize(code_tmp);
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes, res);
                //Записываю код тела в результат (тело сейчас в code_tmp)
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case if_else:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                code_tmp = getCodeFromExpr(node->expr, byteCount, consts, ContextType::ifCondition);
                // Считаю, сколько строк было в подготовке условия
                byteCount += countByteSize(code_tmp);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Получаю байт код тела
                code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount, consts);
                //Считаю размер тела в байтах
                skipBytes = countByteSize(code_tmp);
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes, res);
                //Записываю код тела в результат (тело сейчас в code_tmp)
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                //Получаю байт код блока else
                code_tmp = getCodeFromStmtNode(node->stmt_else, byteCount, consts);
                //Считаю размер блока else
                skipBytes = countByteSize(code_tmp);
                //Записываю в конец главного блока комманду goto со сдвигом на размер else
                Commands::doCommandTwoBytes(go_to, skipBytes, res);
                //Записываю в результат блок else
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                break;
            case end_if:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                code_tmp = getCodeFromExpr(node->expr, byteCount, consts, ContextType::ifCondition);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Нахожу код тела
                for (auto i: node->stmtListMain->vector) {
                    code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount, consts);
                    main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
                }
                //Считаю размер тела в байтах
                skipBytes += countByteSize(main_code);
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes, res);
                //Записываю код тела в результат (тело сейчас в main_code)
                res.insert(res.end(), main_code.begin(), main_code.end());
                break;
            case if_else_endif:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                code_tmp = getCodeFromExpr(node->expr, byteCount, consts, ContextType::ifCondition);
                // Считаю, сколько строк было в подготовке условия
                byteCount += countByteSize(code_tmp);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Получаю байт код тела
                for (auto i: node->stmtListMain->vector) {
                    code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount, consts);
                    main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
                }
                //Считаю размер тела в байтах
                skipBytes += countByteSize(main_code);
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes, res);
                //Записываю код тела в результат (тело сейчас в main_code)
                res.insert(res.end(), main_code.begin(), main_code.end());
                //Получаю байт код блока else
                for (auto i: node->stmtListElse->vector) {
                    code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount, consts);
                    else_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
                }
                //Считаю размер блока else
                skipBytes = countByteSize(else_code);
                //Записываю в конец главного блока комманду goto со сдвигом на размер else
                Commands::doCommandTwoBytes(go_to, skipBytes, res);
                //Записываю в результат блок else
                res.insert(res.end(), else_code.begin(), else_code.end());
                break;
            case if_else_list_endif:
                // Eсли вызывается из условия if, то должен оставить на верху стека 0 или 1, 0 = false, 1 = true
                code_tmp = getCodeFromExpr(node->expr, byteCount, consts, ContextType::ifCondition);
                // Записываю подготовку условия в код
                res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                // Нахожу код тела
                for (auto i: node->stmtListMain->vector) {
                    code_tmp = getCodeFromStmtNode(node->stmt_main, byteCount, consts);
                    main_code.insert(main_code.end(), code_tmp.begin(), code_tmp.end());
                }
                //Считаю размер тела в байтах
                skipBytes += countByteSize(main_code);
                //Записываю код проверки условия со сдвигом на размер тела
                Commands::doCommandTwoBytes(CodeCommandsOneParamTwoBytes::ifeq, skipBytes, res);
                //Записываю код тела в результат (тело сейчас в main_code)
                res.insert(res.end(), main_code.begin(), main_code.end());
                //Записываю код всех else if
                for (auto i: node->listElse->vector) {
                    code_tmp = getCodeFromIfStmt(i, byteCount, consts);
                    res.insert(res.end(), code_tmp.begin(), code_tmp.end());
                }
                break;
        }
    }

    static vector<ValueAndBytes *>
    getCodeFromExpr(ExprNode *node, int currLine, vector<ConstantValue *> &consts, ContextType contextType) {
        if (node == nullptr) return {};
        return {}; // Заглушка
    }

    static int countByteSize(vector<ValueAndBytes *> &code) {
        int res = 0;

        for (auto i: code) {
            res += i->getBytes();
        }

        return res;
    }
};

#endif //PHP_COMPILER_CODEATTRIBUTE_H
