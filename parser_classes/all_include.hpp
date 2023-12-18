#include <string>
#include <vector>

#include "Vector_classes/ClassAccessModList/ClassAccessModList.hpp"
#include "ClassAccessMod/ClassAccessModNode.hpp"

#include "HtmlStmt/HtmlStmtNode.hpp"

#include "Vector_classes/IdList/IdListNode.hpp"

#include "GetValue/GetValueNode.hpp"
#include "Vector_classes/GetValueFuncList/GetValueFuncList.hpp"
#include "GetValueFunc/GetValueFuncNode.hpp"

#include "Vector_classes/GlobalVarList/GlobalVarList.hpp"
#include "GlobalVar/GlobalVarNode.hpp"

#include "InterfaceExprDef/InterfaceExprDefNode.hpp"

#include "ClassDef/ClassDefNode.hpp"

#include "Vector_classes/ExprList.hpp"
#include "Expr/ExprNode.hpp"
#include "Vector_classes/ExprFuncList/ExprFuncList.hpp"
#include "ExprFunc/ExprFuncNode.hpp"

#include "FunctionDef/FunctionDefNode.hpp"

#include "Vector_classes/InterfaceStmtList/InterfaceStmtList.hpp"
#include "InterfaceStmt/InterfaceStmtNode.hpp"
#include "InterfaceStmt/InterfaceStmtDeclNode.hpp"

#include "Vector_classes/StaticVarList/StaticVarList.hpp"
#include "StaticVar/StaticVarNode.hpp"

#include "Vector_classes/ConstDeclList/ConstDeclList.hpp"
#include "ConstDecl/ConstDeclNode.hpp"

#include "ClassStmt/ClassStmtDeclNode.hpp"
#include "ClassStmt/ClassExprNode.hpp"

#include "TraitStmtDecl/TraitStmtDeclNode.hpp"

#include "MatchStmt/MatchArmNode.hpp"
#include "Vector_classes/MatchArmList/MatchArmList.hpp"
#include "MatchStmt/MatchStmtNode.hpp"

#include "Vector_classes/StmtList/StmtList.hpp"
#include "Stmt/StmtNode.hpp"

#include "FunctionStmtDecl/FunctionStmtDeclNode.hpp"

#include "Vector_classes/ClassStmtList/ClassStmtList.hpp"
#include "ClassStmt/ClassStmtNode.hpp"

#include "Vector_classes/CaseDefaultStmtList/CaseDefaultStmtList.hpp"
#include "SwitchCaseStmt/CaseDefaultStmtNode.hpp"

#include "SwitchCaseStmt/SwitchStmtNode.hpp"
// #include "SwitchCaseStmt/CaseDefaultType.cpp"
// #include "TryCatchStmt/TryStmtNode.hpp"      //! Not supported
// #include "TryCatchStmt/CatchStmtNode.hpp"    //! Not supported
#include "Vector_classes/TopStmtList/TopStmtList.hpp"
#include "TopStmt/TopStmtNode.hpp"
// #include "TryCatchStmt/TryCatchStmtNode.hpp" //! Not supported

#include "WhileStmt/WhileStmtNode.hpp"
#include "DoWhileStmt/DoWhileStmtNode.hpp"
#include "ForEachStmt/ForEachStmtNode.hpp"
#include "ForStmt/ForStmtNode.hpp"

#include "IfStmt/IfStmtNode.hpp"
#include "Vector_classes/ElseIfDotList/ElseIfDotList.h"

#include "Start/StartNode.hpp"

void printTreeGraph(StartNode* node);