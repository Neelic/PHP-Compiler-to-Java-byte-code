//
// Created by Dan on 21.01.2024.
//

#ifndef PHP_COMPILER_METHODBYTES_H
#define PHP_COMPILER_METHODBYTES_H


#include "Flags.h"
#include "code_generation/ConstantValue.h"
#include "code_generation/attributes/CodeAttribute.h"
#include "../all_include.hpp"

class MethodBytes {
private:
    Flags flags;
    ConstantValue *name;
    ConstantValue *descriptor;
    CodeAttribute *code = nullptr;
    vector<ConstantValue *> *consts;

public:
    MethodBytes(Flags flags, ConstantValue *name, ConstantValue *descriptor, CodeAttribute *code,
                vector<ConstantValue *> *consts) :
            flags(flags), name(name), descriptor(descriptor), code(code), consts(consts) {
        if (name->getTypeConst() != C_Utf8) throw runtime_error("Name is not Utf-8");
        if (descriptor->getTypeConst() != C_Utf8) throw runtime_error("Descriptor is not Utf-8");
    }

    vector<const ValueAndBytes *> methodToBytes() {
        auto res = vector<const ValueAndBytes *>();

        res.push_back(flags.flagToBytes());
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *name), 2));
        res.push_back(new ValueAndBytes(ConstantValue::getIdConst(consts, *descriptor), 2));

        if (code != nullptr) {
            res.push_back(new ValueAndBytes(1, 2));
            auto codeByteVector = code->attributeToBytes();
            res.insert(res.end(), codeByteVector.begin(), codeByteVector.end());
        } else {
            res.push_back(new ValueAndBytes((int) 0, 2));
        }

        return res;
    }

    static MethodBytes *
    fromFunctionStmtDecl(FunctionStmtDeclNode *node, ClassAccessModList *flagList, vector<ConstantValue *> *consts) {
        if (node == nullptr) return nullptr;

        // Собираю строку дескриптора
        auto descriptor = string("(");

        auto params = vector<string *>();
        auto currParam = string();
        params.push_back(new string("$this")); // По умолчанию добавляю в список параметров первым элементом


        for (auto i: flagList->vector) {
            if (i->access_mod == ClassAccessMod::static_node) {
                params.pop_back(); // Если метод статичен, убираю из списка параметров указатель на класс
            }
        }

        // Для каждого параметра функции кроме последнего
        for (int i = 0; i < (int) (node->function_def->expr_func_list->vector.size() - 1); i++) {
            descriptor += "LRTL/Value;";
            params.push_back(
                    new string("$" + *node->function_def->expr_func_list->vector[i]->get_value_func->id_value));
        }
        // Добавляю последний тип и закрываю
        descriptor += ")LRTL/Value;";

        return new MethodBytes(
                *Flags::convertToFlags(flagList),
                ConstantValue::CreateUtf8(node->function_def->func_id, consts),
                ConstantValue::getConstantByString(consts, &descriptor) ?: ConstantValue::CreateUtf8(
                        &descriptor, consts),
                CodeAttribute::fromStmtList(node->stmt_list, 1000, params, consts),
                consts
        );
    }

    static MethodBytes *fromFunctionDefStmtDecl(FunctionDefNode *node, Flags flags, vector<ConstantValue *> *consts) {
        if (node == nullptr) return nullptr;

        // Собираю строку дескриптора
        auto descriptor = string("(");
        // Для каждого параметра функции кроме последнего
        for (int i = 0; i < node->expr_func_list->vector.size() - 1; i++) {
            descriptor += "LRTL/Value;";
        }
        // Добавляю последний тип и закрываю
        descriptor += ")LRTL/Value;";

        return new MethodBytes(
                flags,
                ConstantValue::CreateUtf8(node->func_id, consts),
                ConstantValue::getConstantByString(consts, &descriptor) ?: ConstantValue::CreateUtf8(
                        &descriptor, consts),
                nullptr,
                consts
        );
    }

    static void getAllConstants(FunctionStmtDeclNode *node, vector<ConstantValue *> &consts) {
        if (node == nullptr) return;

        auto res = vector<ConstantValue *>();

        for (auto stmtNode: node->stmt_list->vector) {


        }
    }

    static void findAllConstInStmtNode(StmtNode *node, vector<ConstantValue *> &consts) {

        if (node == nullptr) return;

        auto res = vector<ConstantValue *>();

        switch (node->type) {

            case expr:
                findConstantInExpr(node->expr_left, consts);
                break;
            case if_stmt:
                findAllConstantsInIfStmt(node->if_stmt, consts);
                break;
            case switch_stmt:
                findAllConstantsInSwitchStmt(node->switch_stmt, consts);
                break;
            case stmt_list:
                for (auto i: node->stmtList->vector)
                    findAllConstInStmtNode(i, consts);
                break;
            case static_var:
                for (auto i: node->static_var->vector) {
                    if (i->id != nullptr) {
                        addConstant(i->id, new string("LRTL/Value;"), consts);
                    }
                }
                break;
            case global_var:
                for (auto i: node->global_var->vector) {
                    if (i->id != nullptr) {
                        addConstant(i->id, new string("LRTL/Value;"), consts);
                    }
                }
                break;
            case while_stmt:
                findConstsInWhileStmt(node->while_stmt, consts);
                break;
            case do_while_stmt:
                findConstsInDoWhile(node->do_while_stmt, consts);
                break;
            case for_stmt:
                findConstsInForStmt(node->for_stmt, consts);
                break;
            case foreach_stmt:
                findConstsInForEachStmt(node->foreach_stmt, consts);
                break;
            case const_decl:
                for (auto i: node->const_decl->vector) {
                    findConstsInConstDeclNode(i, consts);
                }
                break;
        }
    }

    static void findAllConstantsInIfStmt(IfStmtNode *node, vector<ConstantValue *> &consts) {
        if (node == nullptr) return;

        if (node->expr != nullptr)
            findConstantInExpr(node->expr, consts);
        if (node->stmt_main != nullptr)
            findAllConstInStmtNode(node->stmt_main, consts);
        if (node->stmt_else != nullptr)
            findAllConstInStmtNode(node->stmt_else, consts);
        if (node->stmtListMain != nullptr) {
            for (auto i: node->stmtListMain->vector) {
                findAllConstInStmtNode(i, consts);
            }
        }
        if (node->stmtListElse != nullptr) {
            for (auto i: node->stmtListElse->vector) {
                findAllConstInStmtNode(i, consts);
            }
        }
        if (node->listElse != nullptr) {
            for (auto i: node->listElse->vector) {
                findAllConstantsInIfStmt(i, consts);
            }
        }
    }

    static void findAllConstantsInSwitchStmt(SwitchStmtNode *node, vector<ConstantValue *> &consts) {
        if (node == nullptr) return;

        if (node->expr != nullptr) {
            findConstantInExpr(node->expr, consts);
        }

        if (node->defaultStmtList != nullptr) {
            for (auto i: node->defaultStmtList->vector) {
                if (i->expr != nullptr)
                    findConstantInExpr(i->expr, consts);
                if (i->stmtList != nullptr) {
                    for (auto j: i->stmtList->vector) {
                        findAllConstInStmtNode(j, consts);
                    }
                }
            }

        }
    }

    static void findConstsInWhileStmt(WhileStmtNode *node, vector<ConstantValue *> &consts) {
        if (node == nullptr) return;

        if (node->expr != nullptr) {
            findConstantInExpr(node->expr, consts);
        }

        switch (node->type) {
            case while_stmt_type:
                findAllConstInStmtNode(node->stmt, consts);
                break;
            case end_while_stmt_type:
                for (auto i: node->stmtList->vector) {
                    findAllConstInStmtNode(i, consts);
                }
                break;
        }
    }

    static void findConstsInDoWhile(DoWhileStmtNode *node, vector<ConstantValue *> &consts) {
        if (node == nullptr) return;

        findConstantInExpr(node->expr, consts);

        findAllConstInStmtNode(node->stmt, consts);
    }

    static void findConstsInForStmt(ForStmtNode *node, vector<ConstantValue *> &consts) {
        if (node == nullptr) return;

        findConstantInExpr(node->expr_left, consts);

        switch (node->type) {

            case for_stmt_type:
                findAllConstInStmtNode(node->stmt, consts);
                break;
            case for_end_stmt_type:
                for (auto i: node->stmtList->vector) {
                    findAllConstInStmtNode(node->stmt, consts);
                }
                break;
        }

    }

    static void findConstsInForEachStmt(ForEachStmtNode *node, vector<ConstantValue *> &consts) {
        if (node == nullptr) return;

        findConstantInExpr(node->expr_right, consts);

        if (node->id != nullptr) {
            addConstant(node->id, new string("LRTL/Value;"), consts);
        }

        if (node->stmt != nullptr) {
            findAllConstInStmtNode(node->stmt, consts);
        } else if (node->stmtList != nullptr) {
            for (auto i: node->stmtList->vector) {
                findAllConstInStmtNode(node->stmt, consts);
            }
        }
    }

    static void findConstsInConstDeclNode(ConstDeclNode *node, vector<ConstantValue *> &consts) {
        if (node == nullptr) return;
        addConstant(node->id, new string("LRTL/Value;"), consts);
    }

    static void findConstantInExpr(ExprNode *node, vector<ConstantValue *> &consts) {
        if (node == nullptr) return;

        switch (node->exprType) {
            case assign_ref_op:
            case assign_op:
                findConstantInExpr(node->right, consts);
            case variable:
                addConstant(node->id, new string("LRTL/Value;"), consts);
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
                findConstantInExpr(node->left, consts);
                break;
            case class_inst_method_by_ref_op_dots:
                findConstantInExpr(node->left, consts);
                break;
            case set_class_field_op:
                findConstantInExpr(node->right, consts);
                break;
            case class_method_ref_op:
                findConstantInExpr(node->left, consts);
                break;
            case class_inst_field_ref_dots_op:
                findConstantInExpr(node->left, consts);
                break;
            case class_inst_field_by_ref_dots_op:
                findConstantInExpr(node->left, consts);
                break;
            case instance_of:
                findConstantInExpr(node->left, consts);
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
                findConstantInExpr(node->left, consts);
                findConstantInExpr(node->right, consts);
                break;
            case ternary_op:
            case get_array_val:
            case add_array_val:
            case set_array_val:
                findConstantInExpr(node->left, consts);
                findConstantInExpr(node->right, consts);
                findConstantInExpr(node->central, consts);
                break;
            case ref_op:
                findConstantInExpr(node->right, consts);
            default:
                break;
        }
    }

    // Выделил в отдельную функцию, чтоб было не так больно исправлять
    static void addConstant(string *id, string *type, vector<ConstantValue *> &consts) {
        // Проверяю, что константа еще не добавлена
        if (ConstantValue::getConstantByString(&consts, id) == nullptr)
            ConstantValue::CreateUtf8(id,
                                      &consts); // Тут дескриптор и не нужен, потому что это не класс и не метод, а просто имя константы
    }
};


#endif //PHP_COMPILER_METHODBYTES_H
