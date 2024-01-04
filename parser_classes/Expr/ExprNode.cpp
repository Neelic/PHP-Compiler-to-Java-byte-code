#include "ExprNode.hpp"

int ExprNode::GLOBAL_ID = 0;

ExprNode *ExprNode::CreateFromId(std::string *id) {
    auto *tmp = new ExprNode();
    tmp->id = id;
    tmp->exprType = constant;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromFunctionCall(std::string *id, ExprList *listParams) {
    auto *tmp = new ExprNode();
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::call_func;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// From values
ExprNode *ExprNode::CreateFromIntValue(int value) {
    auto *tmp = new ExprNode();
    tmp->int_val = value;
    tmp->exprType = ExprType::int_val;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromFloatValue(float value) {
    auto *tmp = new ExprNode();
    tmp->float_val = value;
    tmp->exprType = ExprType::float_val;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromStringValue(std::string *value) {
    auto *tmp = new ExprNode();
    tmp->string_val = value;
    tmp->exprType = ExprType::string_val;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromComStringValue(std::string *value) {
    auto *tmp = new ExprNode();
    tmp->com_string_val = value;
    tmp->exprType = ExprType::string_val;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromThisKeyword() {
    auto *tmp = new ExprNode();
    tmp->exprType = ExprType::this_keyword;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromSelfKeyword() {
    auto *tmp = new ExprNode();
    tmp->exprType = ExprType::self_keyword;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromParentKeyword() {
    auto *tmp = new ExprNode();
    tmp->exprType = ExprType::parent_keyword;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromGetValueId(GetValueNode *get_value, std::string *id) {
    auto *tmp = new ExprNode();
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->exprType = ExprType::variable;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Assign
ExprNode *ExprNode::CreateFromAssignOp(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::assign_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromAssignRefOp(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::assign_ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Casts
ExprNode *ExprNode::CreateFromIntCast(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::int_cast;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromFloatCast(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::float_cast;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromStringCast(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::string_cast;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromArrayCast(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::array_cast;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromObjectCast(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::object_cast;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBoolCast(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::bool_cast;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Right arrow
ExprNode *ExprNode::CreateFromFieldReference(ExprNode *left, std::string *id) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->exprType = ExprType::class_inst_field_ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromGetValueFieldReference(ExprNode *left, GetValueNode *get_value, std::string *id) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->exprType = ExprType::class_inst_field_ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *
ExprNode::CreateFromGetValueWithExprReference(ExprNode *left, GetValueNode *get_value, ExprNode *get_value_expr) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->get_value = get_value;
    tmp->right = get_value_expr;
    tmp->exprType = ExprType::class_inst_field_by_ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromMethodReference(ExprNode *left, std::string *id, ExprList *listParams) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::class_method_ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromGetValueMethodReference(ExprNode *left, GetValueNode *get_value, std::string *id,
                                                      ExprList *listParams) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->get_value = get_value;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::class_method_ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromGetValueWithExprMethodReference(ExprNode *left, GetValueNode *get_value, std::string *id,
                                                              ExprNode *get_value_expr, ExprList *listParams) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->get_value = get_value;
    tmp->right = get_value_expr;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::class_method_by_ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Quarter Dot
ExprNode *ExprNode::CreateFromFieldReferenceDots(ExprNode *left, std::string *id) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->exprType = ExprType::class_inst_field_ref_dots_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromGetValueFieldReferenceDots(ExprNode *left, GetValueNode *get_value, std::string *id) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->exprType = ExprType::class_inst_field_ref_dots_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *
ExprNode::CreateFromGetValueWithExprReferenceDots(ExprNode *left, GetValueNode *get_value, ExprNode *get_value_expr) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->get_value = get_value;
    tmp->right = get_value_expr;
    tmp->exprType = ExprType::class_inst_field_by_ref_dots_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromMethodReferenceDots(ExprNode *left, std::string *id, ExprList *list) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->id = id;
    tmp->listParams = list;
    tmp->exprType = ExprType::class_inst_method_by_ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromGetValueMethodReferenceDots(ExprNode *left, GetValueNode *get_value, std::string *id,
                                                          ExprList *listParams) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::class_inst_get_value_method_by_ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Math signs
ExprNode *ExprNode::CreateFromAddition(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::plus_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromSubtraction(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::minus_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromMultiplication(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::mult_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromDivision(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::div_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromMod(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::mod_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromPower(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::pow_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Concatenation
ExprNode *ExprNode::CreateFromConcatenation(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::concat_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Boolean operations
ExprNode *ExprNode::CreateFromBooleanOpMore(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_more;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBooleanOpLess(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_less;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBooleanOpOr(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_or;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBooleanOpAnd(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_and;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBooleanOpEqual(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_equal;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBooleanOpEqualStrict(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_equal_strict;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBooleanOpEqualMore(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_equal_more;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBooleanOpEqualLess(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bool_equal_less;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBooleanOpNot(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::bool_not;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Logical

ExprNode *ExprNode::CreateFromLogicOpAnd(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::logic_and;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromLogicOpOr(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::logic_or;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromLogicOpXor(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::logic_xor;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Bitwise
ExprNode *ExprNode::CreateFromShiftLeft(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_shift_l;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromShiftRight(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_shift_r;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBitwiseXor(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_xor;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBitwiseAnd(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_and;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBitwiseOr(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::bitwise_or;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromBitwiseNot(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::bitwise_not;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Unary
ExprNode *ExprNode::CreateFromUnaryPlus(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::u_plus_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromUnaryMinus(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::u_minus_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Clone
ExprNode *ExprNode::CreateFromCloneOp(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::clone_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Ternary
ExprNode *ExprNode::CreateFromTernaryOp(ExprNode *left, ExprNode *central, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->central = central;
    tmp->exprType = ExprType::ternary_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Ref op
ExprNode *ExprNode::CreateFromRefOp(GetValueNode *get_value, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->get_value = get_value;
    tmp->right = right;
    tmp->exprType = ExprType::ref_op;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Array
ExprNode *ExprNode::CreateFromGetArrayVal(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::get_value_array;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromAssignArrayValByExpr(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::add_array_val;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Functions
ExprNode *ExprNode::CreateFromGetValueFunction(std::string *id, ExprList *listParams) {
    auto *tmp = new ExprNode();
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::call_get_value_func;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

// Declarations
ExprNode *ExprNode::CreateFromNewDecl(std::string *id, ExprList *listParams) {
    auto *tmp = new ExprNode();
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::new_decl;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromNewDeclNoParams(std::string *id) {
    auto *tmp = new ExprNode();
    tmp->id = id;
    tmp->exprType = ExprType::new_decl_no_params;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromNewDeclNoId(ExprNode *left) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->exprType = ExprType::new_decl_no_id;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromGetValueDecl(GetValueNode *get_value, std::string *id, ExprList *listParams) {
    auto *tmp = new ExprNode();
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->listParams = listParams;
    tmp->exprType = ExprType::new_get_value_decl;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromGetValueDeclNoParams(GetValueNode *get_value, std::string *id) {
    auto *tmp = new ExprNode();
    tmp->get_value = get_value;
    tmp->id = id;
    tmp->exprType = ExprType::new_get_value_decl_no_params;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

ExprNode *ExprNode::CreateFromInstanceOf(ExprNode *left, ExprNode *right) {
    auto *tmp = new ExprNode();
    tmp->left = left;
    tmp->right = right;
    tmp->exprType = ExprType::instance_of;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}

std::string *ExprNode::idTag() const {
    auto *tmp = new std::string(std::string("Expr") + std::to_string(this->cur_id));
    return tmp;
}

ExprNode *ExprNode::CreateFromNull() {
    auto *tmp = new ExprNode();
    tmp->exprType = ExprType::null_keyword;
    tmp->cur_id = ExprNode::GLOBAL_ID++;
    return tmp;
}
