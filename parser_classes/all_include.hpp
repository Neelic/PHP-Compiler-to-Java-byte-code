#include <string>
#include <vector>

#include "Vector classes/ClassAccessModList/ClassAccessModList.hpp"
#include "ClassAccessMod/ClassAccessModNode.cpp"

#include "HtmlStmt/HtmlStmtNode.cpp"

#include "Vector classes/IdList/IdListNode.hpp"

#include "GetValue/GetValueNode.hpp"
#include "Vector classes/GetValueFuncList/GetValueFuncList.hpp"
#include "GetValueFunc/GetValueFuncNode.hpp"

#include "Vector classes/GlobalVarList/GlobalVarList.hpp"
#include "GlobalVar/GlobalVarNode.hpp"

#include "InterfaceExprDef/InterfaceExprDefNode.hpp"

#include "ClassDef/ClassDefNode.hpp"

#include "Vector classes/ExprList.hpp"
#include "Expr/ExprNode.hpp"
#include "Vector classes/ExprFuncList/ExprFuncList.hpp"
#include "ExprFunc/ExprFuncNode.hpp"

#include "FunctionDef/FunctionDefNode.hpp"

#include "Vector classes/InterfaceStmtList/InterfaceStmtList.hpp"
#include "InterfaceStmt/InterfaceStmtNode.hpp"
#include "InterfaceStmt/InterfaceStmtDeclNode.hpp"

#include "Vector classes/StaticVarList/StaticVarList.hpp"
#include "StaticVar/StaticVarNode.hpp"

#include "Vector classes/ConstDeclList/ConstDeclList.hpp"
#include "ConstDecl/ConstDeclNode.hpp"

#include "ClassStmt/ClassStmtDeclNode.hpp"
#include "ClassStmt/ClassExprNode.hpp"

#include "TraitStmtDecl/TraitStmtDeclNode.hpp"

#include "MatchStmt/MatchArmNode.hpp"
#include "Vector classes/MatchArmList/MatchArmList.hpp"
#include "MatchStmt/MatchStmtNode.hpp"

#include "Vector classes/StmtList/StmtList.hpp"
#include "Stmt/StmtNode.hpp"

#include "FunctionStmtDecl/FunctionStmtDeclNode.hpp"

#include "Vector classes/ClassStmtList/ClassStmtList.hpp"
#include "ClassStmt/ClassStmtNode.hpp"

#include "Vector classes/CaseDefaultStmtList/CaseDefaultStmtList.hpp"
#include "SwitchCaseStmt/CaseDefaultStmtNode.hpp"

#include "SwitchCaseStmt/SwitchStmtNode.hpp"
// #include "SwitchCaseStmt/CaseDefaultType.cpp"
// #include "TryCatchStmt/TryStmtNode.hpp"      //! Not supported
// #include "TryCatchStmt/CatchStmtNode.hpp"    //! Not supported
#include "Vector classes/TopStmtList/TopStmtList.hpp"
#include "TopStmt/TopStmtNode.hpp"
// #include "TryCatchStmt/TryCatchStmtNode.hpp" //! Not supported

#include "WhileStmt/WhileStmtNode.hpp"
#include "DoWhileStmt/DoWhileStmtNode.hpp"
#include "ForEachStmt/ForEachStmtNode.hpp"
#include "ForStmt/ForStmtNode.hpp"

#include "IfStmt/IfStmtNode.hpp"

#include "Start/StartNode.cpp"

extern std::string GRAPH_STR("digraph Tree {\n");