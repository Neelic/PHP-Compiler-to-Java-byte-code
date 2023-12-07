%{
#include <stdio.h>
#include "parser.tab.h"

void yyerror(char* str);
extern int yylex(void);
%}

%code requires {
#include <string>
#include <vector>
#include "parser_classes/all_include.hpp"
using namespace std;

class IfStmtNode;
class ExprNode;
class StmtNode;
class GetValueNode;
class TopStmtNode;
class FunctionStmtDeclNode;
class ClassStmtDeclNode;
class InterfaceStmtDeclNode;
class TraitStmtDeclNode;
class StartNode;
class SwitchStmtNode;
class CaseDefaultStmtNode;
class ForStmtNode;
class ForEachStmtNode;
class WhileStmtNode;
class DoWhileStmtNode;
class MatchStmtNode;
class MatchArmNode;
class HtmlStmtNode;
class ClassDefNode;
class ClassAccessMode;
class ClassStmtNode;
class ClassExprNode;
class InterfaceExprDefNode;
class InterfaceStmtNode;
class FunctionDefNode;
class GetValueFuncNode;
class StartStmtNode;
class ExprList;
class TopStmtList;
class CaseDefaultStmtList;
class ClassAccessModList;
class ClassStmtList;
class ConstDeclList;
class ExprFuncList;
class GetValueFuncList;
class GlobalVarList;
class IdListNode;
class InterfaceStmtList;
class MatchArmList;
class StaticVarList;
class StmtList;

}

%union{
        string* sval;
        int ival;
        float fval;
        IfStmtNode* if_stmt_union;
        ExprNode* expr_union;
        StmtNode* stmt_union;
        GetValueNode* get_value_union;
        ExprList* expr_list_union;
        TopStmtNode* top_stmt_union;
        FunctionStmtDeclNode* function_stmt_decl_union;
        ClassStmtDeclNode* class_stmt_decl_union;
        InterfaceStmtDeclNode* interface_stmt_decl_union;
        TraitStmtDeclNode* trait_stmt_decl_union;
        TopStmtList* top_stmt_list_union;
        StartNode* start_union;
        SwitchStmtNode* switch_stmt_union;
        CaseDefaultStmtList* case_default_stmt_list_union;
        CaseDefaultStmtNode* case_default_stmt_union;
        ForStmtNode* for_stmt_union;
        ForEachStmtNode* foreach_stmt_union;
        WhileStmtNode* while_stmt_union;
        DoWhileStmtNode* do_while_stmt_union;
        MatchStmtNode* match_stmt_union;
        MatchArmList* match_stmt_list_union;
        MatchArmNode* match_arm_union;
        StaticVarList* static_var_list_union;
        GlobalVarList* global_var_list_union;
        StmtList* stmt_list_union;
        HtmlStmtNode* html_stmt_union;
        IdListNode* id_list_union;
        ConstDeclList* const_decl_list_union;
        ClassDefNode* class_def_union;
        ClassStmtList* class_stmt_list_union;
        ClassAccessMod class_access_mod_union;
        ClassAccessModList* class_access_mod_list_union;
        ClassStmtNode* class_stmt_union;
        ClassExprNode* class_expr_union;
        InterfaceExprDefNode* interface_expr_def_union;
        InterfaceStmtList* interface_stmt_list_union;
        InterfaceStmtNode* interface_stmt_union;
        FunctionDefNode* function_def_union;
        ExprFuncList* expr_func_list_union;
        GetValueFuncNode* get_value_func_union;
        vector<GetValueFuncNode*>* get_value_func_list_union;
        }

%token START_CODE_PHP_TAG
%token END_CODE_PHP_TAG
%token <sval> HTML

%token <sval> ID
%token <ival> INT_NUMBER
%token <fval> FLOAT_NUMBER
%token <sval> STRING
%token <sval> COM_STRING
%token CONST
%token RETURN

%token TRY
%token CATCH
%token FINALLY

%token MATCH

%token FOR
%token END_FOR
%token WHILE
%token END_WHILE
%token DO
%token FOREACH
%token AS
%token END_FOREACH
%token CONTINUE

%token IF
%token ELSE
%token END_IF
%token SWITCH
%token CASE
%token BREAK
%token DEFAULT
%token END_SWITCH

%token FUNCTION
%token FN
%token USE
%token GLOBAL
%token T_ECHO

%token CLASS
%token ABSTRACT
%token EXTENDS
%token IMPLEMENTS
%right PUBLIC PRIVATE PROTECTED FINAL STATIC READ_ONLY
%token INTERFACE
%token TRAIT
%token THIS
%token SELF

%right THROW
%left LOGIC_OR
%left LOGIC_XOR
%left LOGIC_AND
%right '='
%left BOOLEAN_OR
%left BOOLEAN_AND
%right '?' ':'
%left '|'
%left '^'
%left '&'
%nonassoc EQUAL EQUAL_STRICT EQU_NOT
%nonassoc '>' '<' EQU_MORE EQU_LESS
%left SHIFT_L SHIFT_R
%left '.'
%left '-' '+'
%right INC DEC
%left '/' '*' '%'
%right '!'
%right '~' U_MINUS U_PLUS INT_CAST FLOAT_CAST STRING_CAST ARRAY_CAST OBJECT_CAST BOOL_CAST
%left '['']' R_ARROW R_DOUBLE_ARROW QUARTER_DOT
%right POW
%nonassoc '('')'
%nonassoc NEW CLONE

%type <start_union> start
%type <top_stmt_union> top_stmt
%type <if_stmt_union> if_stmt
%type <expr_union> expr
%type <expr_union> expr_may_empty
%type <stmt_union> stmt
%type <get_value_union> get_value
%type <expr_list_union> expr_list
%type <expr_list_union> expr_list_not_e
%type <function_stmt_decl_union> function_stmt_decl
%type <class_stmt_decl_union> class_stmt_decl
%type <interface_stmt_decl_union> interface_stmt_decl
%type <trait_stmt_decl_union> trait_stmt_decl
%type <top_stmt_list_union> top_stmt_list_not_e
%type <switch_stmt_union> switch_stmt
%type <case_default_stmt_list_union> case_default_stmt_list
%type <case_default_stmt_union> case_default_stmt
%type <for_stmt_union> for_stmt
%type <foreach_stmt_union> foreach_stmt
%type <while_stmt_union> while_stmt
%type <do_while_stmt_union> do_while_stmt
%type <match_stmt_union> match_stmt
%type <match_stmt_list_union> match_stmt_list
%type <match_stmt_list_union> match_stmt_list_not_e
%type <match_arm_union> match_arm
%type <static_var_list_union> static_var_list
%type <global_var_list_union> global_var_list
%type <stmt_list_union> stmt_list
%type <stmt_list_union> stmt_list_may_empty
%type <html_stmt_union> html_stmt
%type <id_list_union> id_list
%type <const_decl_list_union> const_decl_list_not_e
%type <class_def_union> class_def
%type <class_stmt_list_union> class_stmt_list
%type <class_access_mod_union> class_access_mod
%type <class_access_mod_list_union> class_access_mod_list
%type <class_stmt_list_union> class_stmt_list_not_e
%type <class_stmt_union> class_stmt
%type <class_expr_union> class_expr
%type <interface_expr_def_union> interface_expr_def
%type <interface_stmt_list_union> interface_stmt_list
%type <interface_stmt_list_union> interface_stmt_list_not_e
%type <interface_stmt_union> interface_stmt
%type <function_def_union> function_def
%type <expr_func_list_union> expr_func_list
%type <get_value_func_union> get_value_func
%type <get_value_func_list_union> get_value_func_list_not_e
%type <expr_func_list_union> expr_func_list_not_e 

%%

start:    START_CODE_PHP_TAG top_stmt_list_not_e                                      {$$=StartStmtNode::Create($2);}                     
        | START_CODE_PHP_TAG top_stmt_list_not_e END_CODE_PHP_TAG                     {$$=StartStmtNode::Create($2);}
        | START_CODE_PHP_TAG top_stmt_list_not_e END_CODE_PHP_TAG HTML                {$$=StartStmtNode::Create($2);}
        | HTML START_CODE_PHP_TAG top_stmt_list_not_e                                 {$$=StartStmtNode::Create($3);}
        | HTML START_CODE_PHP_TAG top_stmt_list_not_e END_CODE_PHP_TAG                {$$=StartStmtNode::Create($3);}
        | HTML START_CODE_PHP_TAG top_stmt_list_not_e END_CODE_PHP_TAG HTML           {$$=StartStmtNode::Create($3);}
        | START_CODE_PHP_TAG                                                          {}
        | START_CODE_PHP_TAG END_CODE_PHP_TAG                                         {}
        | START_CODE_PHP_TAG END_CODE_PHP_TAG HTML                                    {}
        | HTML                                                                        {}
        ;

top_stmt_list_not_e: top_stmt                                                         {vector<TopStmtNode*> tmp; tmp.push_back($1); $$=TopStmtList::Create(&tmp);}                                                                                                           
                |    top_stmt_list_not_e top_stmt                                     {$$=$1->Insert($2);}
                ;

top_stmt: stmt                                                                        {$$=TopStmtNode::CreateFromStmt($1);}
        | function_stmt_decl                                                          {$$=TopStmtNode::CreateFromFunctionDecl($1);}
        | class_stmt_decl                                                             {$$=TopStmtNode::CreateFromClassDecl($1);}
        | interface_stmt_decl                                                         {$$=TopStmtNode::CreateFromInterfaceDecl($1);}
        | trait_stmt_decl                                                             {$$=TopStmtNode::CreateFromTraitDecl($1);}
        ;

get_value: '$'                                                                        {$$=GetValueNode::Create();}
        |  get_value '$'                                                              {$1->count+=1;$$=$1;}
        ;

if_stmt:  IF '(' expr ')' stmt                                                        {$$=IfStmtNode::CreateFromIfStmt($3, $5);}
        | IF '(' expr ')' stmt ELSE stmt                                              {$$=IfStmtNode::CreateFromCreateFromIfElseStmt($3, $5, $7);}
        | IF '(' expr ')' ':' stmt_list_may_empty END_IF ';'                          {$$=IfStmtNode::CreateFromIfEndIfStmt($3, $6);}
        | IF '(' expr ')' ':' stmt_list_may_empty ELSE stmt_list_may_empty END_IF ';' {$$=IfStmtNode::CreateFromIfElseEndIfStmt($3, $6, $8);}  
        ;

switch_stmt: SWITCH '(' expr ')' '{' '}'                                              {$$=SwitchStmtNode::CreateFromSwitchStmt($3);}                                       
        |    SWITCH '(' expr ')' '{' case_default_stmt_list '}'                       {$$=SwitchStmtNode::CreateFromSwitchDefaultStmt($3, $6);}
        |    SWITCH '(' expr ')' ':' case_default_stmt_list END_SWITCH ';'            {$$=SwitchStmtNode::CreateFromSwitchDefaultEndswitchStmt($3, $6);}
        ;

case_default_stmt_list: case_default_stmt                                             {vector<CaseDefaultStmtNode*>tmp;tmp.push_back($1);$$=CaseDefaultStmtList::Create(&tmp);}                          
                |       case_default_stmt_list case_default_stmt                      {$$=$1->Insert($2);}
                ;

case_default_stmt: CASE expr ':' stmt_list_may_empty                                  {$$=CaseDefaultStmtNode::CreateFromCaseStmt($2, $4);}
                |  DEFAULT ':' stmt_list_may_empty                                    {$$=CaseDefaultStmtNode::CreateFromDefaultStmt($3);}
                |  FINALLY '{' stmt_list_may_empty '}'                                {$$=CaseDefaultStmtNode::CreateFromFinallyStmt($3);}
                ;

for_stmt: FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' stmt                                 {$$=ForStmtNode::CreateFromForStmt($3, $5, $7, $9);}
        | FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' ':' stmt_list_may_empty END_FOR ';'  {$$=ForStmtNode::CreateFromForEndStmt($3, $5, $7, $10);}
        ;

foreach_stmt: FOREACH '(' expr AS expr ')' stmt                                                                 {$$=ForEachStmtNode::CreateFromForeachStmt($3, $5, $7);}
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW '$' ID ')' stmt                                           {$$=ForEachStmtNode::CreateFromForeachRightArrowStmt($3, $5, $8, $10);}
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW '&' '$' ID ')' stmt                                       {$$=ForEachStmtNode::CreateFromForeachRightArrowPointerStmt($3, $5, $9, $11);}
        |     FOREACH '(' expr AS expr ')' ':' stmt_list_may_empty END_FOREACH ';'                              {$$=ForEachStmtNode::CreateFromEndForeachStmt($3, $5, $8);}
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW '$' ID ')' ':' stmt_list_may_empty END_FOREACH ';'        {$$=ForEachStmtNode::CreateFromEndForeachRightArrowStmt($3, $5, $8, $11);}
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW '&' '$' ID ')' ':' stmt_list_may_empty END_FOREACH ';'    {$$=ForEachStmtNode::CreateFromEndForeachRightArrowPointerStmt($3, $5, $9, $12);}
        ;

while_stmt: WHILE '(' expr ')' stmt                                                   {$$=WhileStmtNode::CreateFromWhileStmt($3, $5);}
        |   WHILE '(' expr ')' ':' stmt_list_may_empty END_WHILE ';'                  {$$=WhileStmtNode::CreateFromEndWhileStmt($3, $6);}
        ;

do_while_stmt: DO stmt WHILE '(' expr ')' ';'                                         {$$=DoWhileStmtNode::CreateFromDoWhileStmt($2, $5);}
        ;

match_stmt: MATCH '(' expr ')' '{' match_stmt_list '}' ';'                            {$$=MatchStmtNode::CreateFromMatchStmtNode($3, $6);}
        ;

match_stmt_list:  match_stmt_list_not_e                                               {$$=$1;}
                | /* empty */                                                         {}
                ;

match_stmt_list_not_e:    match_arm                                                   {vector<MatchArmNode*>tmp;tmp.push_back($1);$$=MatchArmList::Create(&tmp);}
                        | match_stmt_list_not_e ',' match_arm                         {$$=$1->Insert($3);}
                        ;

match_arm: expr_list_not_e R_DOUBLE_ARROW expr                                        {$$=MatchArmNode::CreateFromMatchArmStmt($1, $3);}
        |  DEFAULT R_DOUBLE_ARROW expr                                                {$$=MatchArmNode::CreateFromDefaultArmStmt($3);}
        |  DEFAULT ',' R_DOUBLE_ARROW expr                                            {$$=MatchArmNode::CreateFromDefaultArmWithCommaStmt($4);}
        ;

try_stmt: TRY '{' stmt_list_may_empty '}'                                             {/*! not supported */}
        ;

catch_stmt: CATCH'(' ID '$' ID ')' '{' stmt_list_may_empty '}'                        {/*! not supported */}
        |   CATCH'(' ID ')' '{' stmt_list_may_empty '}'                               {/*! not supported */}
        ;

catch_stmt_list:  catch_stmt                                                          {/*! not supported */}
                | catch_stmt_list catch_stmt                                          {/*! not supported */}
                ;

try_catch_stmt:   try_stmt catch_stmt_list                                            {/*! not supported */}
                | try_stmt                                                            {/*! not supported */}
                ;

stmt:     expr_may_empty ';'                                                          {$$=StmtNode::CreateFromExpr($1);}
        | if_stmt                                                                     {$$=StmtNode::CreateFromIfStmt($1);}
        | switch_stmt                                                                 {$$=StmtNode::CreateFromSwitchStmt($1);}
        | '{'stmt_list'}'                                                             {$$=StmtNode::CreateFromStmtList($2);}
        | STATIC static_var_list ';'                                                  {$$=StmtNode::CreateFromStaticVar($2);}
        | GLOBAL global_var_list ';'                                                  {$$=StmtNode::CreateFromGlobalVar($2);}
        | while_stmt                                                                  {$$=StmtNode::CreateFromWhileStmt($1);}
        | do_while_stmt                                                               {$$=StmtNode::CreateFromDoWhileStmt($1);}
        | for_stmt                                                                    {$$=StmtNode::CreateFromForStmt($1);}
        | foreach_stmt                                                                {$$=StmtNode::CreateFromForEachStmt($1);}
        | THROW expr ';'                                                              {$$=StmtNode::CreateFromThrowStmt($2);}
        | try_catch_stmt                                                              {/*! not supported?*/}
        | match_stmt                                                                  {$$=StmtNode::CreateFromMatchStmt($1);}
        | CONST const_decl_list_not_e ';'                                             {$$=StmtNode::CreateFromConstDecl($2);}
        | RETURN expr_may_empty ';'                                                   {$$=StmtNode::CreateFromReturnStmt($2);}
        | html_stmt                                                                   {$$=StmtNode::CreateFromHtmlStmt($1);}
        | BREAK ';'                                                                   {$$=StmtNode::CreateFromBreakStmt();}
        | T_ECHO expr ';'                                                             {$$=StmtNode::CreateFromTEchoStmt($2);}
        | CONTINUE ';'                                                                {$$=StmtNode::CreateFromContinueStmt();}
        ;

static_var_list:  '$' ID                                                              {vector<StaticVarNode*>tmp; tmp.push_back(StaticVarNode::CreateFromId($2)); $$=StaticVarList::Create(&tmp);}
                | '$' ID '=' expr                                                     {vector<StaticVarNode*>tmp; tmp.push_back(StaticVarNode::CreateFromIdAssign($2, $4)); $$=StaticVarList::Create(&tmp);}
                | static_var_list ',' '$' ID                                          {$$=$1->Insert($4);}
                | static_var_list ',' '$' ID '=' expr                                 {$$=$1->Insert(StaticVarNode::CreateFromIdAssign($4, $6));}
                ;

global_var_list:  get_value ID                                                        {vector<GlobalVarNode*>tmp; tmp.push_back(GlobalVarNode::CreateFromGlobalValue($1, $2)); $$=GlobalVarList::Create(&tmp);}
                | global_var_list ',' get_value ID                                    {$$=$1->Insert(GlobalVarNode::CreateFromGlobalValue($3, $4));}                    
                ;

stmt_list: stmt                                                                       {vector<StmtNode*>tmp;tmp.push_back($1);$$=StmtList::Create(&tmp);}
	|  stmt_list stmt                                                             {$$=$1->Insert($2);}
        ;

stmt_list_may_empty: stmt_list                                                        {$$=$1;}
                |    /* empty */                                                      {}
                ;

html_stmt: END_CODE_PHP_TAG HTML START_CODE_PHP_TAG                  {$$=HtmlStmtNode::Create($2);}
        ;

expr:     INT_NUMBER                                                 {$$=ExprNode::CreateFromIntValue($1);}
        | FLOAT_NUMBER                                               {$$=ExprNode::CreateFromFloatValue($1);}
        | STRING                                                     {$$=ExprNode::CreateFromStringValue($1);}
        | COM_STRING                                                 {$$=ExprNode::CreateFromComStringValue($1);}
        | '$' THIS                                                   {$$=ExprNode::CreateFromThisKeyword();}
        | SELF                                                       {$$=ExprNode::CreateFromSelfKeyword();}
        | get_value ID                                               {$$=ExprNode::CreateFromGetValueId($1, $2);}
        | ID                                                         {$$=ExprNode::CreateFromId($1);}
        | expr '=' expr                                              {$$=ExprNode::CreateFromAssignOp($1, $3);}
        | expr '=' '&' expr                                          {$$=ExprNode::CreateFromAssignRefOp($1, $4);}
        | INT_CAST expr                                              {$$=ExprNode::CreateFromIntCast($2);}
        | FLOAT_CAST expr                                            {$$=ExprNode::CreateFromFloatCast($2);}
        | STRING_CAST expr                                           {$$=ExprNode::CreateFromStringCast($2);}
        | ARRAY_CAST expr                                            {$$=ExprNode::CreateFromArrayCast($2);}
        | OBJECT_CAST expr                                           {$$=ExprNode::CreateFromObjectCast($2);}
        | BOOL_CAST expr                                             {$$=ExprNode::CreateFromBoolCast($2);}
        | expr R_ARROW ID                                            {$$=ExprNode::CreateFromFieldReference($1, $3);}
        | expr R_ARROW get_value ID                                  {$$=ExprNode::CreateFromGetValueFieldReference($1, $3, $4);}
        | expr R_ARROW get_value '{' expr '}'                        {$$=ExprNode::CreateFromGetValueWithExprReference($1, $3, $5);}
        | expr R_ARROW ID '(' expr_list ')'                          {$$=ExprNode::CreateFromMethodReference($1, $3, $5);}
        | expr R_ARROW get_value ID '(' expr_list ')'                {$$=ExprNode::CreateFromGetValueMethodReference($1, $3, $4, $6);}
        | expr R_ARROW get_value ID '{' expr '}' '(' expr_list ')'   {$$=ExprNode::CreateFromGetValueWithExprMethodReference($1, $3, $4, $6, $9);}
        | expr QUARTER_DOT ID                                        {$$=ExprNode::CreateFromFieldReferenceDots($1, $3);}
        | expr QUARTER_DOT get_value ID                              {$$=ExprNode::CreateFromGetValueFieldReferenceDots($1, $3, $4);}
        | expr QUARTER_DOT get_value '{' expr '}'                    {$$=ExprNode::CreateFromGetValueWithExprReferenceDots($1, $3, $5);}
        | '(' expr ')'                                               {$$=$2;}
        | expr '-' expr                                              {$$=ExprNode::CreateFromSubtraction($1, $3);}
        | expr '+' expr                                              {$$=ExprNode::CreateFromAddition($1, $3);}
        | expr '*' expr                                              {$$=ExprNode::CreateFromMultiplication($1, $3);}
        | expr '/' expr                                              {$$=ExprNode::CreateFromDivision($1, $3);}
        | expr '%' expr                                              {$$=ExprNode::CreateFromMod($1, $3);}
        | expr POW expr                                              {$$=ExprNode::CreateFromPower($1, $3);}
        | expr '.' expr                                              {$$=ExprNode::CreateFromConcatenation($1, $3);}
        | expr '>' expr                                              {$$=ExprNode::CreateFromBooleanOpMore($1, $3);}
        | expr '<' expr                                              {$$=ExprNode::CreateFromBooleanOpLess($1, $3);}
        | expr BOOLEAN_OR expr                                       {$$=ExprNode::CreateFromBooleanOpOr($1, $3);}
        | expr BOOLEAN_AND expr                                      {$$=ExprNode::CreateFromBooleanOpAnd($1, $3);}
        | expr LOGIC_OR expr                                         {$$=ExprNode::CreateFromLogicOpOr($1, $3);}
        | expr LOGIC_XOR expr                                        {$$=ExprNode::CreateFromLogicOpXor($1, $3);}
        | expr LOGIC_AND expr                                        {$$=ExprNode::CreateFromLogicOpAnd($1, $3);}
        | expr EQUAL expr                                            {$$=ExprNode::CreateFromBooleanOpEqual($1, $3);}
        | expr EQUAL_STRICT expr                                     {$$=ExprNode::CreateFromBooleanOpEqualStrict($1, $3);}
        | expr EQU_NOT expr                                          {}
        | expr EQU_MORE expr                                         {$$=ExprNode::CreateFromBooleanOpEqualMore($1, $3);}
        | expr EQU_LESS expr                                         {$$=ExprNode::CreateFromBooleanOpEqualLess($1, $3);}
        | expr SHIFT_L expr                                          {$$=ExprNode::CreateFromShiftLeft($1, $3);}
        | expr SHIFT_R expr                                          {$$=ExprNode::CreateFromShiftRight($1, $3);}
        | expr '^' expr                                              {$$=ExprNode::CreateFromBitwiseXor($1, $3);}
        | expr '|' expr                                              {$$=ExprNode::CreateFromBitwiseOr($1, $3);}
        | expr '&' expr                                              {$$=ExprNode::CreateFromBitwiseAnd($1, $3);}
        | '-' expr %prec U_MINUS                                     {$$=ExprNode::CreateFromUnaryMinus($2);}
        | '+' expr %prec U_PLUS                                      {$$=ExprNode::CreateFromUnaryPlus($2);}
        | '!' expr                                                   {$$=ExprNode::CreateFromBooleanOpNot($2);}
        | '~' expr                                                   {$$=ExprNode::CreateFromBitwiseNot($2);}
        | CLONE expr                                                 {$$=ExprNode::CreateFromCloneOp($2);}
        | expr '?' expr ':' expr                                     {$$=ExprNode::CreateFromTernaryOp($1, $3, $5);}
        | expr '?' ':' expr                                          {$$=ExprNode::CreateFromTernaryOp($1, NULL, $4);}
        | get_value '{' expr '}'                                     {$$=ExprNode::CreateFromRefOp($1, $3);}
        | expr '[' expr ']'                                          {$$=ExprNode::CreateFromGetArrayVal($1, $3);}
        | expr '[' ']' '=' expr                                      {$$=ExprNode::CreateFromAssignArrayValByExpr($1, $5);}
        | ID '(' expr_list ')'                                       {$$=ExprNode::CreateFromGetValueFunction($1, $3);}
        | get_value ID brackets                                      {/*! not supported */}
        | anon_function_expr                                         {/*! not supported */}
        | NEW ID '(' expr_list ')'                                   {$$=ExprNode::CreateFromNewDecl($2, $4);}
        | NEW ID                                                     {$$=ExprNode::CreateFromNewDeclNoParams($2);}
        | NEW get_value ID                                           {$$=ExprNode::CreateFromGetValueDeclNoParams($2, $3);}
        | NEW get_value ID '(' expr_list ')'                         {$$=ExprNode::CreateFromGetValueDecl($2, $3, $5);}
        | NEW '(' expr ')'                                           {$$=ExprNode::CreateFromNewDeclNoId($3);}
        ;

expr_may_empty: expr                                                 {$$=$1;}
                | /* empty */                                        {}
                ;

brackets: '(' expr_list ')'
        | brackets '(' expr_list ')'
        ;

id_list:  ID                                                         {vector<string*>tmp;tmp.push_back($1);$$=IdListNode::Create(&tmp);}
        | id_list ',' ID                                             {$$=$1->Insert($3);}
        ;

expr_list_not_e:  expr                                               {vector<ExprNode*> tmp; tmp.push_back($1); $$=ExprList::Create(&tmp);}
                | expr_list_not_e ',' expr                           {$$=$1->Insert($3);}
                ;

expr_list: expr_list_not_e                                           {$$=$1;}
	| /* empty */                                                {}
        ;

const_decl_list_not_e:    ID '=' expr                                {vector<ConstDeclNode*>tmp;tmp.push_back(ConstDeclNode::CreateFromConstDeclaration($1, $3));$$=ConstDeclList::Create(&tmp);}
                        | const_decl_list_not_e ',' ID '=' expr      {$$=$1->Insert(ConstDeclNode::CreateFromConstDeclaration($3, $5));}
                        ;

class_def: CLASS ID                                                  {$$=ClassDefNode::CreateFromClassDef($2);}                     
        |  CLASS ID EXTENDS ID                                       {$$=ClassDefNode::CreateFromExtendedDef($2, $4);}
        |  CLASS ID IMPLEMENTS id_list                               {$$=ClassDefNode::CreateFromImplementDef($2, $4);}
        |  CLASS ID EXTENDS ID IMPLEMENTS id_list                    {$$=ClassDefNode::CreateFromExtendedImplementedDef($2, $4, $6);}                   
        ;

class_stmt_decl:  class_def '{' class_stmt_list '}'                  {$$=ClassStmtDeclNode::CreateFromNoModDefinition($1, $3);}
                | FINAL class_def '{' class_stmt_list '}'            {$$=ClassStmtDeclNode::CreateFromFinalModDefinition($2, $4);}
                | ABSTRACT class_def '{' class_stmt_list '}'         {$$=ClassStmtDeclNode::CreateFromAbstractModDefinition($2, $4);}
                ;

class_stmt_list: class_stmt_list_not_e                               {$$=$1;}
                | /* empty */                                        {}
                ;

class_access_mod: PUBLIC                                             {$$=ClassAccessMod::public_node;}
                | PROTECTED                                          {$$=ClassAccessMod::private_node;}
                | PRIVATE                                            {$$=ClassAccessMod::protected_node;}
                | FINAL                                              {$$=ClassAccessMod::final_node;}
                | ABSTRACT                                           {$$=ClassAccessMod::abstract_node;}
                | READ_ONLY                                          {$$=ClassAccessMod::read_only_node;}
                | STATIC                                             {$$=ClassAccessMod::static_node;}
                ;

class_access_mod_list:    class_access_mod                           {vector<ClassAccessMod>tmp;tmp.push_back($1);$$=ClassAccessModList::Create(&tmp);}
                        | class_access_mod_list class_access_mod     {$$=$1->Insert($2);}
                        ;

class_stmt_list_not_e:    class_stmt                                 {vector<ClassStmtNode*>tmp;tmp.push_back($1);$$=ClassStmtList::Create(&tmp);}
                        | class_stmt_list_not_e class_stmt           {$$=$1->Insert($2);}
                        ;

class_stmt: class_expr ';'                                           {$$=ClassStmtNode::CreateFromClassExpr($1);}
        |   class_access_mod_list function_stmt_decl                 {$$=ClassStmtNode::CreateFromFunctionStmtDecl($1, $2);}
        |   USE id_list ';'                                          {$$=ClassStmtNode::CreateFromIdList($2);}
        |   class_stmt_decl                                          {$$=ClassStmtNode::CreateFromClassStmtDecl($1);}
        ;       

class_expr: class_access_mod_list get_value ID '=' expr              {$$=ClassExprNode::CreateFromGetValueAssign($1, $2, $3, $5);}
        |   class_access_mod_list get_value ID                       {$$=ClassExprNode::CreateFromGetValue($1, $2, $3);}
        |   class_access_mod_list CONST const_decl_list_not_e ';'    {$$=ClassExprNode::CreateFromConstant($1, $3);}
        ;

interface_expr_def: INTERFACE ID                                     {$$=InterfaceExprDefNode::CreateFromNoExtendedDefinition($2);}
                |   INTERFACE ID EXTENDS id_list                     {$$=InterfaceExprDefNode::CreatedFromDefinitionWithExtended($2, $4);}
                ;

interface_stmt_decl: interface_expr_def '{' interface_stmt_list '}'  {$$=InterfaceStmtDeclNode::Create($1, $3);}
                ;

interface_stmt_list: interface_stmt_list_not_e                       {$$=$1;}
                |    /* empty */                                     {}
                ;

interface_stmt_list_not_e: interface_stmt                            {vector<InterfaceStmtNode*>tmp;tmp.push_back($1);$$=InterfaceStmtList::Create(&tmp);}
                        |  interface_stmt_list_not_e interface_stmt  {$$=$1->Insert($2);}
                        ;

interface_stmt: class_access_mod_list function_def ';'               {$$=InterfaceStmtNode::Create($1, $2);}
                ;

trait_stmt_decl: TRAIT ID  '{' class_stmt_list '}'                   {$$=TraitStmtDeclNode::Create($2, $4);}
                ;

function_def: FUNCTION ID '(' expr_func_list ')'                     {$$=FunctionDefNode::CreateFromDefWithNoType($2, $4);}
        |     FUNCTION ID '(' expr_func_list ')' ':' ID              {$$=FunctionDefNode::CreateFromDefWithType($2, $4, $7);}
        ;

function_stmt_decl: function_def '{' stmt_list '}'                   {$$=FunctionStmtDeclNode::Create($1, $3);}
                ;

anon_function_expr: anon_function_stmt_decl                           {/*! not supported */}
                |   anon_function_short_stmt_decl                     {/*! not supported */}
                ;

expr_func_list:   expr_func_list_not_e                               {$$=$1;}
                | /* empty */                                        {}
                ;

get_value_func:   '&' '$' ID                                         {$$=GetValueFuncNode::CreateFromRefValue($3);}
                | '$' ID                                             {$$=GetValueFuncNode::CreateFromGetValue($2);}
                | ID '&' '$' ID                                      {$$=GetValueFuncNode::CreateFromRefValueWithType($4, $1);}
                | ID '$' ID                                          {$$=GetValueFuncNode::CreateFromGetValueWithType($3, $1);}
                ;

get_value_func_list_not_e: get_value_func                                       {vector<GetValueFuncNode*>tmp;tmp.push_back($1);$$=GetValueFuncList::Create(&tmp);}
                        |  get_value_func_list_not_e ',' get_value_func         {$$=$1->Insert($3);}
                        ;

expr_func_list_not_e: get_value_func                                            {vector<ExprFuncNode*>tmp;tmp.push_back(ExprFuncNode::CreateFromGetValueFunc($1));$$=ExprFuncList::Create(&tmp);}
                |     get_value_func '=' expr                                   {vector<ExprFuncNode*>tmp;tmp.push_back(ExprFuncNode::CreateFromGetValueFuncAssign($1, $3));$$=ExprFuncList::Create(&tmp);}
                |     expr_func_list_not_e ',' get_value_func                   {$1.push_back(ExprFuncNode::CreateFromGetValueFunc($3));$$=$1;}
                |     expr_func_list_not_e ',' get_value_func '=' expr          {$1.push_back(ExprFuncNode::CreateFromGetValueFunc(ExprFuncNode::CreateFromGetValueFuncAssign($3, $5)));$$=$1;}
                ;

anon_function_def: FUNCTION '(' expr_func_list ')'                                                      {/*! not supported */}
                |  FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'                {/*! not supported */}
                |  STATIC FUNCTION '(' expr_func_list ')'                                               {/*! not supported */}
                |  STATIC FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'         {/*! not supported */}
                |  FUNCTION '(' expr_func_list ')' ':' ID                                               {/*! not supported */}
                |  FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')' ':' ID         {/*! not supported */}
                |  STATIC FUNCTION '(' expr_func_list ')' ':' ID                                        {/*! not supported */}
                |  STATIC FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')' ':' ID  {/*! not supported */}
                ;

anon_function_stmt_decl: anon_function_def '{' stmt_list '}'      {/*! not supported */}
                        ;

anon_function_short_def:  FN '(' expr_func_list ')'               {/*! not supported */}
                        | FN '(' expr_func_list ')' ':' ID        {/*! not supported */}
                        | STATIC FN '(' expr_func_list ')'        {/*! not supported */}
                        | STATIC FN '(' expr_func_list ')' ':' ID {/*! not supported */}
                        ;

anon_function_short_stmt_decl: anon_function_short_def R_DOUBLE_ARROW expr
                        ;

%%

void yyerror(char* str) {
        fprintf(stderr, "ERROR: %s\n", str);
}