#include "ExprNode.hpp"

ExprNode* ExprNode::CreateFromId(std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->id = id;
    tmp->exprType = constant;
    return tmp;
}

ExprNode* ExprNode::CreateFromFunctionCall(std::string* id, std::vector<ExprNode*>* listParams)
{
    ExprNode* tmp = new ExprNode();
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::ref_op // Не нашел типа для функции, или просто не понял
    return tmp;
}

ExprNode* ExprNode::CreateFromIntValue( int value)
{
    ExprNode* tmp = new ExprNode();
    tmp->int_val = value;
    tmp->exprType = ExprType::int_val;
    return tmp;
}

ExprNode* ExprNode::CreateFromFloatValue( float value)
{
    ExprNode* tmp = new ExprNode();
    tmp->float_val = value;
    tmp->exprType = ExprType::float_val;
    return tmp;
}

ExprNode* ExprNode::CreateFromStringValue(std::string* value)
{
    ExprNode* tmp = new ExprNode();
    tmp->string_val = value;
    tmp->exprType = ExprType::string_val;
    return tmp;
}

ExprNode* ExprNode::CreateFromComStringValue(std::string* value)
{
    ExprNode* tmp = new ExprNode();
    tmp->com_string_val = value;
    tmp->exprType = ExprType::string_val;
    return tmp;
}

ExprNode* ExprNode::CreateFromGetValueId(GetValueNode* get_value, std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->exprType = ExprType::variable;
    return tmp;
}

ExprNode* ExprNode::CreateFromAssignOp(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::assign_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromAssignRefOp(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::assign_ref_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromIntCast(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::int_cast;
    return tmp;
}

ExprNode* ExprNode::CreateFromFloatCast(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::float_cast;
    return tmp;
}

ExprNode* ExprNode::CreateFromStringCast(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::string_cast;
    return tmp;
}

ExprNode* ExprNode::CreateFromArrayCast(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::array_cast;
    return tmp;
}

ExprNode* ExprNode::CreateFromObjectCast(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::object_cast;
    return tmp;
}

ExprNode* ExprNode::CreateFromBoolCast(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::bool_cast;
    return tmp;
}


