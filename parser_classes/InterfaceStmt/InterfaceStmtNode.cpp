#include "InterfaceStmtNode.hpp"

InterfaceStmtNode* InterfaceStmtNode::Create(ClassAccessModList* access_mod, FunctionDefNode* function_def)
{
    InterfaceStmtNode* tmp = new InterfaceStmtNode();
    tmp->access_mod = access_mod;
    tmp->function_def = function_def;
    return tmp;
}