#include "AnonFunctionDefNode.hpp"

AnonFunctionDefNode* AnonFunctionDefNode::CreateFromAnonFunctionDef(std::vector<ExprNode*>* listParams)
{
    AnonFunctionDefNode* tmp = new AnonFunctionDefNode();
    tmp->listParams = listParams;
    tmp->def_type = AnonFunctionDefType::anon_func;
    return tmp;
}

AnonFunctionDefNode* AnonFunctionDefNode::CreateFromAnonFunctionDefWithInherit(std::vector<ExprNode*>* listParams,
                                                                                std::vector<GetValueFunc*>* getValueFuncList)
{
    AnonFunctionDefNode* tmp = new AnonFunctionDefNode();
    tmp->listParams = listParams;
    tmp->getValueFuncList = getValueFuncList;
    tmp->def_type = AnonFunctionDefType::func_with_inherit;
    return tmp;
}

AnonFunctionDefNode* AnonFunctionDefNode::CreateFromStaticAnonFunctionDef(std::vector<ExprNode*>* listParams)
{
    AnonFunctionDefNode* tmp = new AnonFunctionDefNode();
    tmp->listParams = listParams;
    tmp->def_type = AnonFunctionDefType::static_func;
    return tmp;
}

AnonFunctionDefNode* AnonFunctionDefNode::CreateFromStaticAnonFuncDefWithInherit(std::vector<ExprNode*>* listParams,
                                                                                std::vector<GetValueFunc*>* getValueFuncList)
{
    AnonFunctionDefNode* tmp = new AnonFunctionDefNode();
    tmp->listParams = listParams;
    tmp->getValueFuncList = getValueFuncList;
    tmp->def_type = AnonFunctionDefType::static_func_with_inherit;
    return tmp;
}

AnonFunctionDefNode* AnonFunctionDefNode::CreateFromAnonFuncDefWithType(std::vector<ExprNode*>* listParams, std::string* id)
{
    AnonFunctionDefNode* tmp = new AnonFunctionDefNode();
    tmp->listParams = listParams;
    tmp->id = id;
    tmp->def_type = AnonFunctionDefType::func_with_type;
    return tmp;
}

AnonFunctionDefNode* AnonFunctionDefNode::CreateFromAnonFuncDefWithInheritAndType(std::vector<ExprNode*>* listParams, 
                                                                                std::vector<GetValueFunc*>* getValueFuncList,
                                                                                std::string* id)
{
    AnonFunctionDefNode* tmp = new AnonFunctionDefNode();
    tmp->listParams = listParams;
    tmp->getValueFuncList = getValueFuncList;
    tmp->id = id;
    tmp->def_type = AnonFunctionDefType::func_with_inherit_and_type;
    return tmp;
}

AnonFunctionDefNode* AnonFunctionDefNode::CreateFromStaticAnonFuncDefWithInheritAndType(std::vector<ExprNode*>* listParams, 
                                                                                std::vector<GetValueFunc*>* getValueFuncList,
                                                                                std::string* id)
{
    AnonFunctionDefNode* tmp = new AnonFunctionDefNode();
    tmp->listParams = listParams;
    tmp->getValueFuncList = getValueFuncList;
    tmp->id = id;
    tmp->def_type = AnonFunctionDefType::static_func_with_inherit_and_type;
    return tmp;
}