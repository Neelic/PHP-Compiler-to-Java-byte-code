//
// Created by Dan on 23.01.2024.
//

#ifndef PHP_COMPILER_CODEATTRIBUTE_H
#define PHP_COMPILER_CODEATTRIBUTE_H


#include "code_generation/ConstantValue.h"
#include "TableAttribute.h"
#include "StmtList.hpp"
#include "StmtNode.hpp"
#include "StaticVarList.hpp"
#include "StaticVarNode.hpp"
#include "GlobalVarList.hpp"
#include "GlobalVarNode.hpp"
#include "parser_classes/Vector_classes/ConstDeclList/ConstDeclList.hpp"
#include "parser_classes/ConstDecl/ConstDeclNode.hpp"

class CodeAttribute {
private:
    ConstantValue *name;
    int maxStack;
    int maxLocals;
    vector<ValueAndBytes *> *code;
    vector<TableAttribute *> attributes;
    vector<ConstantValue *> *consts;

    int getAttrLength() {
        int res = 12; //exclude first 6 bytes
        res += getCodeLength();
        for (auto table: attributes) {
            res += table->getAttributeLength();
        }

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

    void addAttribute(TableAttribute *attr) {
        attributes.push_back(attr);
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

        res.push_back(new ValueAndBytes((int) attributes.size(), 2));
        for (auto table: attributes) {
            auto tableBytes = table->attributeToBytes();
            res.insert(res.end(), tableBytes.begin(), tableBytes.end());
        }

        return res;
    }

    static CodeAttribute *
    fromStmtList(StmtList *node, int maxLocals, vector<ConstantValue *> &params, vector<ConstantValue *> &consts) {
        if (node == nullptr) return nullptr;
        CodeAttribute *res;

        auto code = vector<ValueAndBytes *>();

        int byteCount = 0;

        for (auto i: node->vector) {
            switch (i->type) {

                case StmtType::stmt_list:
                    res = fromStmtList(i->stmtList, maxLocals, consts);
                    break;
                case StmtType::static_var:
                    if (i->static_var == nullptr) break;
                    for (auto j: i->static_var->vector) {
                        // Разобраться со сбором констант
                    }
                    break;
                case StmtType::global_var:
                    if (i->global_var == nullptr) break;
                    for (auto j: i->global_var->vector) {
                        // Разобраться со сбором констант
                    }
                    break;
                case StmtType::const_decl:
                    if (i->const_decl == nullptr) break;

                    for (auto j: i->const_decl->vector) {
                        // Разобраться со сбором констант
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
            }

        }
    }

    const vector<ValueAndBytes *> getCodeFromStmtList(StmtList *node, int currLine, vector<ConstantValue *> &consts) {

    }
};

#endif //PHP_COMPILER_CODEATTRIBUTE_H
