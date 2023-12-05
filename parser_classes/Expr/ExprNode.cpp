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
    tmp->exprType = ExprType::call_func;
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

ExprNode* ExprNode::CreateFromMethodReference(ExprNode* left, std::string* id, std::vector<ExprNode*>* listParams)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::class_method_ref_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromGetValueMethodReference(ExprNode* left, GetValueNode* get_value, std::string* id, std::vector<ExprNode*>* listParams)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->get_value = get_value;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::class_method_ref_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromGetValueWithExprMethodReference(ExprNode* left, GetValueNode* get_value, std::string* id, ExprNode* get_value_expr, std::vector<ExprNode*>* listParams)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->get_value = get_value;
    tmp->right = get_value_expr;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::class_method_by_ref_op;
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

//Math signs
ExprNode* ExprNode::CreateFromAddition(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::plus_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromSubtraction(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::minus_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromMultiplication(ExprNode* left, ExprNode* right)
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
ExprNode* ExprNode::CreateFromConcatenation(ExprNode* left, ExprNode* right)
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

//Unary
ExprNode* ExprNode::CreateFromUnaryPlus(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::u_plus_op;
    return tmp;
}

ExprNode* ExprNode::CreateFromUnaryMinus(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::u_minus_op;
    return tmp;
}

//Clone
ExprNode* ExprNode::CreateFromCloneOp(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::clone_op;
    return tmp;
}

//Ternary
ExprNode* ExprNode::CreateFromTernaryOp(ExprNode* left, ExprNode* right, ExprNode* central)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->central = central;
    tmp->exprType = ExprType::ternary_op;
    return tmp;
}

//Ref op
ExprNode* ExprNode::CreateFromRefOp(GetValueNode* get_value, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->get_value = get_value;
    tmp->right = right;
    tmp->exprType = ExprType::ref_op;
    return tmp;
}

//Array
ExprNode* ExprNode::CreateFromGetArrayVal(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::get_value_array;
    return tmp;
}
//TODO ЭТОГО НЕТ В ПАРСЕРЕ
ExprNode* ExprNode::CreateFromArrayValueById(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::get_array_val;
    return tmp;
}

ExprNode* ExprNode::CreateFromAssignArrayValById(ExprNode* left, ExprNode* right)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::add_array_val;
    return tmp;
}
//TODO ДО ЭТОГО МОМЕНТА
//Functions
ExprNode* ExprNode::CreateFromGetValueFunction(std::string* id, std::vector<ExprNode*>* listParams)
{
    ExprNode* tmp = new ExprNode();
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::call_get_value_func;
    return tmp;
}

//Declarations
ExprNode* ExprNode::CreateFromNewDecl(std::string* id, std::vector<ExprNode*>* listParams)
{
    ExprNode* tmp = new ExprNode();
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::new_decl;
    return tmp;
}

ExprNode* ExprNode::CreateFromNewDeclNoParams(std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->id = id;
    tmp->exprType = ExprType::new_decl_no_params;
    return tmp;
}

ExprNode* ExprNode::CreateFromNewDeclNoId(ExprNode* left)
{
    ExprNode* tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::new_decl_no_id;
    return tmp;
}

ExprNode* ExprNode::CreateFromGetValueDecl(GetValueNode* get_value, std::string* id, std::vector<ExprNode*>* listParams)
{
    ExprNode* tmp = new ExprNode();
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::new_get_value_decl;
    return tmp;
}

ExprNode* ExprNode::CreateFromGetValueDeclNoParams(GetValueNode* get_value, std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->exprType = ExprType::new_get_value_decl_no_params;
    return tmp;
}



