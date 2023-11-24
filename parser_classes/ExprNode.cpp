#include "ExprType.cpp"
#include "GetValueNode.cpp"
#include <string>
#include <vector>

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
    static ExprNode* CreateFromIntValue(int int_val);
    static ExprNode* CreateFromFloatValue(float float_val);
    static ExprNode* CreateFromStringValue(std::string* string_val);
    static ExprNode* CreateFromComStringValue(std::string* string_com_val);
    static ExprNode* CreateFromGetValueId(GetValueNode* get_value, std::string* id);
    //TODO продолжить список
};

ExprNode* ExprNode::CreateFromId(std::string* id)
{
    ExprNode* tmp = new ExprNode();
    tmp->id = id;
    tmp->exprType = constant;
    return tmp;
}

ExprNode *ExprNode::CreateFromFunctionCall(std::string* id, std::vector<ExprNode*>* listParams)
{
    return nullptr;
}
