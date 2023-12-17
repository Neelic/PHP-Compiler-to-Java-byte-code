#include "InterfaceStmtNode.hpp"

int InterfaceStmtNode::GLOBAL_ID = 0;

std::string *InterfaceStmtNode::idTag() const {
    auto* tmp = new std::string(std::string("InterfaceStmt") + std::to_string(this->cur_id));
    return tmp;
}

InterfaceStmtNode* InterfaceStmtNode::CreateNode(ClassAccessModList* access_mod, FunctionDefNode* function_def)
{
    InterfaceStmtNode* tmp = new InterfaceStmtNode();
    tmp->access_mod = access_mod;
    tmp->function_def = function_def;
    tmp->cur_id = InterfaceStmtNode::GLOBAL_ID++;
    return tmp;
}