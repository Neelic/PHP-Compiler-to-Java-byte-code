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
    tmp->exprType = ExprType::ref_op; // Не нашел типа для функции, или просто не понял
    return tmp;
}

//From values
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

//Assign
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

//Casts
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

//Right arrow
ExprNode* ExprNode::CreateFromFieldReference(ExprNode* left, std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->exprType = ExprType::class_inst_field_ref_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromGetValueFieldReference(ExprNode* left, GetValueNode* get_value, std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->exprType = ExprType::class_inst_field_ref_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromGetValueWithExprReference(ExprNode* left, GetValueNode* get_value, ExprNode* get_value_expr)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->get_value = get_value;
    tmp->right = get_value_expr;
    tmp->exprType = ExprType::class_inst_field_by_ref_op;
    return tmp;
}

//Quarter Dot
ExprNode* ExprNode::CreateFromFieldReferenceDots(ExprNode* left, std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->exprType = ExprType::class_inst_field_ref_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromGetValueFieldReferenceDots(ExprNode* left, GetValueNode* get_value, std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->exprType = ExprType::class_inst_field_ref_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromGetValueWithExprReferenceDots(ExprNode* left, GetValueNode* get_value, ExprNode* get_value_expr)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->get_value = get_value;
    tmp->right = get_value_expr;
    tmp->exprType = ExprType::class_inst_field_by_ref_op;
    return tmp;
}

//Brackets
ExprNode* ExprNode::CreateFromExprInBrackets(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::bracket;
    return tmp;
}

//Math signs
ExprNode* ExprNode::CreateFromAddition(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::plus_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromSubstraction(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::minus_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromMultipliction(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::mult_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromDivision(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::div_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromMod(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::mod_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromPower(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::pow_op;
    return tmp;
}

//Concatenation
ExprNode* ExprNode::CreateFromPower(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::concat_op;
    return tmp;
}

//Boolean operations
ExprNode* ExprNode::CreateFromBooleanOpMore(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_more;
    return tmp;
}

ExprNode* ExprNode::CreateFromBooleanOpLess(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_less;
    return tmp;
}

ExprNode* ExprNode::CreateFromBooleanOpOr(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_or;
    return tmp;
}

ExprNode* ExprNode::CreateFromBooleanOpAnd(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_and;
    return tmp;
}

ExprNode* ExprNode::CreateFromBooleanOpEqual(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_equal;
    return tmp;
}

ExprNode* ExprNode::CreateFromBooleanOpEqualStrict(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_equal_strict;
    return tmp;
}

ExprNode* ExprNode::CreateFromBooleanOpEqualMore(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_equal_more;
    return tmp;
}

ExprNode* ExprNode::CreateFromBooleanOpEqualLess(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_equal_less;
    return tmp;
}

ExprNode* ExprNode::CreateFromBooleanOpNot(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::bool_not;
    return tmp;
}

//Logical

ExprNode* ExprNode::CreateFromLogicOpAnd(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::logic_and;
    return tmp;
}

ExprNode* ExprNode::CreateFromLogicOpOr(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::logic_or;
    return tmp;
}

ExprNode* ExprNode::CreateFromLogicOpXor(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::logic_xor;
    return tmp;
}

//Bitwise
ExprNode* ExprNode::CreateFromShiftLeft(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_shift_l;
    return tmp;
}

ExprNode* ExprNode::CreateFromShiftRight(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_shift_r;
    return tmp;
}

ExprNode* ExprNode::CreateFromBitwiseXor(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_xor;
    return tmp;
}

ExprNode* ExprNode::CreateFromBitwiseAnd(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_and;
    return tmp;
}

ExprNode* ExprNode::CreateFromBitwiseOr(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_or;
    return tmp;
}

ExprNode* ExprNode::CreateFromBitwiseNot(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_not;
    return tmp;
}

//Uni






