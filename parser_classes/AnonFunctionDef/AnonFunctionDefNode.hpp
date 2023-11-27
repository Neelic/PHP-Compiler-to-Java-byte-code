#include "AnonFunctionDefType.cpp"

class AnonFunctionDefNode
{
public:
    AnonFunctionDefType def_type;
    std::vector<ExprNode*>* listParams;
    std::vector<GetValueFunc*>* getValueFuncList;
    std::string* id;

    static AnonFunctionDefNode* CreateFromAnonFunctionDef(std::vector<ExprNode*>* listParams);
    static AnonFunctionDefNode* CreateFromAnonFunctionDefWithInherit(std::vector<ExprNode*>* listParams, std::vector<GetValueFunc*>* getValueFuncList);
    static AnonFunctionDefNode* CreateFromStaticAnonFunctionDef(std::vector<ExprNode*>* listParams);
    static AnonFunctionDefNode* CreateFromStaticAnonFuncDefWithInherit(std::vector<ExprNode*>* listParams, std::vector<GetValueFunc*>* getValueFuncList);
    static AnonFunctionDefNode* CreateFromAnonFuncDefWithType(std::vector<ExprNode*>* listParams, std::string* id);
    static AnonFunctionDefNode* CreateFromAnonFuncDefWithInheritAndType(std::vector<ExprNode*>* listParams, std::vector<GetValueFunc*>* getValueFuncList, std::string* id);
    static AnonFunctionDefNode* CreateFromStaticAnonFuncDefWithInheritAndType(std::vector<ExprNode*>* listParams, std::vector<GetValueFunc*>* getValueFuncList, std::string* id);


};