#include "TryCatchStmtNode.hpp"

TryCatchStmtNode* TryCatchStmtNode::CreateFromTryCatchStmt(TryStmtNode* try_stmt, std::vector<CatchStmtNode*>* catch_stmt_list)
{
    TryCatchStmtNode* tmp = new TryCatchStmtNode();
    tmp->try_stmt = try_stmt;
    tmp->catch_stmt_list = catch_stmt_list;
    tmp->type = TryCatchStmtType::try_catch;
    return tmp;
}

TryCatchStmtNode* TryCatchStmtNode::CreateFromTryStmt(TryStmtNode* try_stmt)
{
    TryCatchStmtNode* tmp = new TryCatchStmtNode();
    tmp->try_stmt = try_stmt;
    tmp->type = TryCatchStmtType::try_only;
    return tmp;
}
