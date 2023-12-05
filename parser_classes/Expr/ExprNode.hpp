#include "ExprType.cpp"
#include <string>
#include <vector>

class GetValueNode;

class ExprNode
{
public:
    ExprType exprType;
    int int_val;
    float float_val;
    std::string* string_val;
    std::string* com_string_val;
    std::string* id;
    GetValueNode* get_value;
    ExprNode* left;
    ExprNode* right;
    ExprNode* central;
    std::vector<ExprNode*>* listParams;

    static ExprNode* CreateFromId(std::string* id);
    static ExprNode* CreateFromFunctionCall(std::string* id, std::vector<ExprNode*>* listParams);
    //From values
    static ExprNode* CreateFromIntValue(int int_val);
    static ExprNode* CreateFromFloatValue(float float_val);
    static ExprNode* CreateFromStringValue(std::string* string_val);
    static ExprNode* CreateFromComStringValue(std::string* string_com_val);
    static ExprNode* CreateFromGetValueId(GetValueNode* get_value, std::string* id);
    //Assign
    static ExprNode* CreateFromAssignOp(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromAssignRefOp(ExprNode* left, ExprNode* right);
    //Casts
    static ExprNode* CreateFromIntCast(ExprNode* left);
    static ExprNode* CreateFromFloatCast(ExprNode* left);
    static ExprNode* CreateFromStringCast(ExprNode* left);
    static ExprNode* CreateFromArrayCast(ExprNode* left);
    static ExprNode* CreateFromObjectCast(ExprNode* left);
    static ExprNode* CreateFromBoolCast(ExprNode* left);
    //Right arrow
    static ExprNode* CreateFromFieldReference(ExprNode* left, std::string* id);
    static ExprNode* CreateFromGetValueFieldReference(ExprNode* left, GetValueNode* get_value, std::string* id);
    static ExprNode* CreateFromGetValueWithExprReference(ExprNode* left, GetValueNode* get_value, ExprNode* get_value_expr);
    
    static ExprNode* CreateFromMethodReference(ExprNode* left, std::string* id, std::vector<ExprNode*>* listParams);
    static ExprNode* CreateFromGetValueMethodReference(ExprNode* left, GetValueNode* get_value, std::string* id, std::vector<ExprNode*>* listParams);
    static ExprNode* CreateFromGetValueWithExprMethodReference(ExprNode* left, GetValueNode* get_value, std::string* id, ExprNode* get_value_expr, std::vector<ExprNode*>* listParams);
    //Quarter Dot
    static ExprNode* CreateFromFieldReferenceDots(ExprNode* left, std::string* id);
    static ExprNode* CreateFromGetValueFieldReferenceDots(ExprNode* left, GetValueNode* get_value, std::string* id);
    static ExprNode* CreateFromGetValueWithExprReferenceDots(ExprNode* left, GetValueNode* get_value, ExprNode* get_value_expr);
    //Math signs
    static ExprNode* CreateFromSubtraction(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromAddition(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromMultiplication(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromDivision(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromMod(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromPower(ExprNode* left, ExprNode* right);
    //Concatenation
    static ExprNode* CreateFromConcatenation(ExprNode* left, ExprNode* right);
    //Boolean operations
    static ExprNode* CreateFromBooleanOpMore(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBooleanOpLess(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBooleanOpOr(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBooleanOpAnd(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBooleanOpEqual(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBooleanOpEqualStrict(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBooleanOpEqualMore(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBooleanOpEqualLess(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBooleanOpNot(ExprNode* left);
    //Logical
    static ExprNode* CreateFromLogicOpAnd(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromLogicOpOr(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromLogicOpXor(ExprNode* left, ExprNode* right);
    //Bitwise
    static ExprNode* CreateFromShiftLeft(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromShiftRight(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBitwiseXor(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBitwiseAnd(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBitwiseOr(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromBitwiseNot(ExprNode* left, ExprNode* right);
    //Unary
    static ExprNode* CreateFromUnaryPlus(ExprNode* left);
    static ExprNode* CreateFromUnaryMinus(ExprNode* left);
    //Clone
    static ExprNode* CreateFromCloneOp(ExprNode* left);
    //Ternary
    static ExprNode* CreateFromTernaryOp(ExprNode* left, ExprNode* right, ExprNode* central);
    //Ref op - уточнить
    static ExprNode* CreateFromRefOp(GetValueNode* get_value, ExprNode* right);
    //Array
    static ExprNode* CreateFromGetArrayVal(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromArrayValueById(ExprNode* left, ExprNode* right);
    static ExprNode* CreateFromAssignArrayValById(ExprNode* left, ExprNode* right);
    //Functions
    static ExprNode* CreateFromGetValueFunction(std::string* id, std::vector<ExprNode*>* listParams);

    //Declaration
    static ExprNode* CreateFromNewDecl(std::string* id, std::vector<ExprNode*>* listParams);
    static ExprNode* CreateFromNewDeclNoParams(std::string* id);
    static ExprNode* CreateFromNewDeclNoId(ExprNode* left);
    static ExprNode* CreateFromGetValueDecl(GetValueNode* get_value, std::string* id, std::vector<ExprNode*>* listParams);
    static ExprNode* CreateFromGetValueDeclNoParams(GetValueNode* get_value, std::string* id);

    //TODO продолжить список
};