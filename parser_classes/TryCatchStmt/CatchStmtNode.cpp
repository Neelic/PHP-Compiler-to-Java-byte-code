#include "CatchStmtNode.hpp"

CatchStmtNode* CatchStmtNode::CreateFromCatchStmt(std::string* id_type, std::string* id_value, std::vector<StmtNode*>* stmtList)
{
    CatchStmtNode* tmp = new CatchStmtNode();
    tmp->id_type = id_type;
    tmp->id_value = id_value;
    tmp->stmtList = stmtList;
    tmp->type = CatchStmtType::type_and_value;
    return tmp;
}

CatchStmtNode* CatchStmtNode::CreateFromCatchStmtOnlyType(std::string* id_type, std::vector<StmtNode*>* stmtList)
{
    CatchStmtNode* tmp = new CatchStmtNode();
    tmp->id_type = id_type;
    tmp->stmtList = stmtList;
    tmp->type = CatchStmtType::only_type;
    return tmp;
}
