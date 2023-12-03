#include "InterfaceStmtNode.hpp"

InterfaceStmtNode* InterfaceStmtNode::Create(std::vector<ClassAccessMod>* access_mod, FunctionDefNode* function_def)
{
    InterfaceStmtNode* tmp = new InterfaceStmtNode();
    tmp->access_mod = access_mod;
    tmp->function_def = function_def;
    return tmp;
}