%{
#include <stdio.h>
#include "parser_classes/all_include.hpp"
extern int yylex();
void yyerror(char* str);
%}

%token START_CODE_PHP_TAG
%token END_CODE_PHP_TAG
%token HTML

%token ID
%token INT_NUMBER
%token FLOAT_NUMBER
%token STRING
%token COM_STRING
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

%union{
        std::string* sval;
        int ival;
        float fval;
        IfStmtNode* if_stmt_union;
        ExprNode* expr_union;
        StmtNode* stmt_union;
        GetValueNode* get_value_union;
        }

%type <if_stmt_union> if_stmt
%type <expr_union> expr
%type <stmt_union> stmt
%type <get_value_union> get_value

%%

start:    START_CODE_PHP_TAG top_stmt_list_not_e
        | START_CODE_PHP_TAG top_stmt_list_not_e END_CODE_PHP_TAG
        | START_CODE_PHP_TAG top_stmt_list_not_e END_CODE_PHP_TAG HTML
        | HTML START_CODE_PHP_TAG top_stmt_list_not_e
        | HTML START_CODE_PHP_TAG top_stmt_list_not_e END_CODE_PHP_TAG
        | HTML START_CODE_PHP_TAG top_stmt_list_not_e END_CODE_PHP_TAG HTML
        | START_CODE_PHP_TAG
        | START_CODE_PHP_TAG END_CODE_PHP_TAG
        | START_CODE_PHP_TAG END_CODE_PHP_TAG HTML
        | HTML
        ;

top_stmt_list_not_e: top_stmt
                |    top_stmt_list_not_e top_stmt
                ;

top_stmt: stmt
        | function_stmt_decl
        | class_stmt_decl
        | interface_stmt_decl
        | trait_stmt_decl
        ;

get_value: '$'
        |  get_value '$'
        ;

if_stmt:  IF '(' expr ')' stmt                                                        {/*$$ = IfStmtNode::CreateFromIfStmt($3, $5);*/}
        | IF '(' expr ')' stmt ELSE stmt                                              {/*$$ = IfStmtNode::CreateFromCreateFromIfElseStmt($3, $5, $7);*/}
        | IF '(' expr ')' ':' stmt_list_may_empty END_IF ';'                          {/*$$ = IfStmtNode::CreateFromIfEndIfStmt($3, $6);*/}
        | IF '(' expr ')' ':' stmt_list_may_empty ELSE stmt_list_may_empty END_IF ';' {/*$$ = IfStmtNode::CreateFromIfElseEndIfStmt($3, $6, $8);*/}  
        ;

switch_stmt: SWITCH '(' expr ')' '{' '}'
        |    SWITCH '(' expr ')' '{' case_default_stmt_list '}'
        |    SWITCH '(' expr ')' ':' case_default_stmt_list END_SWITCH ';'
        ;

case_default_stmt_list: case_default_stmt
                |       case_default_stmt_list case_default_stmt
                ;

case_default_stmt: CASE expr ':' stmt_list_may_empty
                |  DEFAULT ':' stmt_list_may_empty
                |  FINALLY '{' stmt_list_may_empty '}' 
                ;

for_stmt: FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' stmt
        | FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' ':' stmt_list_may_empty END_FOR ';'
        ;

foreach_stmt: FOREACH '(' expr AS expr ')' stmt
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW '$' ID ')' stmt
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW '&' '$' ID ')' stmt
        |     FOREACH '(' expr AS expr ')' ':' stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW '$' ID ')' ':' stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW '&' '$' ID ')' ':' stmt_list_may_empty END_FOREACH ';'
        ;

while_stmt: WHILE '(' expr ')' stmt
        |   WHILE '(' expr ')' ':' stmt_list_may_empty END_WHILE ';'
        ;

do_while_stmt: DO stmt WHILE '(' expr ')' ';'
        ;

match_stmt: MATCH '(' expr ')' '{' match_stmt_list '}' ';'
        ;

match_stmt_list:  match_stmt_list_not_e
                | /* empty */
                ;

match_stmt_list_not_e:    match_arm 
                        | match_stmt_list_not_e ',' match_arm
                        ;

match_arm: expr_list_not_e R_DOUBLE_ARROW expr
        |  DEFAULT R_DOUBLE_ARROW expr
        |  DEFAULT ',' R_DOUBLE_ARROW expr
        ;

try_stmt: TRY '{' stmt_list_may_empty '}' {/*! not supported */}
        ;

catch_stmt: CATCH'(' ID '$' ID ')' '{' stmt_list_may_empty '}'
        |   CATCH'(' ID ')' '{' stmt_list_may_empty '}'
        ;

catch_stmt_list:  catch_stmt
                | catch_stmt_list catch_stmt
                ;

try_catch_stmt:   try_stmt catch_stmt_list {/*! not supported */}
                | try_stmt
                ;

stmt:     expr_may_empty ';'
        | if_stmt
        | switch_stmt
        | '{'stmt_list'}'
        | STATIC static_var_list ';'
        | GLOBAL global_var_list ';'
        | while_stmt
        | do_while_stmt
        | for_stmt
        | foreach_stmt
        | THROW expr ';'
        | try_catch_stmt
        | match_stmt
        | CONST const_decl_list_not_e ';'
        | RETURN expr_may_empty ';'
        | html_stmt
        | BREAK ';'
        | T_ECHO expr ';'
        | CONTINUE ';'
        ;

static_var_list:  '$' ID
                | '$' ID '=' expr
                | static_var_list ',' '$' ID
                | static_var_list ',' '$' ID '=' expr
                ;

global_var_list:  get_value ID
                | global_var_list ',' get_value ID
                ;

stmt_list: stmt
	|  stmt_list stmt
        ;

stmt_list_may_empty: stmt_list
                |    /* empty */
                ;

html_stmt: END_CODE_PHP_TAG HTML START_CODE_PHP_TAG
        ;

expr:     INT_NUMBER
        | FLOAT_NUMBER
        | STRING
        | COM_STRING
        | get_value THIS
        | SELF
        | get_value ID
        | ID
        | expr '=' expr
        | expr '=' '&' expr
        | INT_CAST expr
        | FLOAT_CAST expr
        | STRING_CAST expr
        | ARRAY_CAST expr
        | OBJECT_CAST expr
        | BOOL_CAST expr
        | expr R_ARROW ID
        | expr R_ARROW get_value ID
        | expr R_ARROW get_value '{' expr '}'
        | expr R_ARROW ID '(' expr_list ')'
        | expr R_ARROW get_value ID '(' expr_list ')'
        | expr R_ARROW get_value ID '{' expr '}' '(' expr_list ')'
        | expr QUARTER_DOT ID
        | expr QUARTER_DOT get_value ID
        | expr QUARTER_DOT get_value '{' expr '}'
        | '(' expr ')'
        | expr '-' expr
        | expr '+' expr
        | INC expr
        | DEC expr
        | expr '*' expr
        | expr '/' expr
        | expr '%' expr
        | expr POW expr
        | expr '.' expr
        | expr '>' expr
        | expr '<' expr
        | expr BOOLEAN_OR expr
        | expr BOOLEAN_AND expr
        | expr LOGIC_OR expr
        | expr LOGIC_XOR expr
        | expr LOGIC_AND expr
        | expr EQUAL expr 
        | expr EQUAL_STRICT expr
        | expr EQU_NOT expr
        | expr EQU_MORE expr
        | expr EQU_LESS expr
        | expr SHIFT_L expr
        | expr SHIFT_R expr
        | expr '^' expr
        | expr '|' expr
        | expr '&' expr
        | '-' expr %prec U_MINUS
        | '+' expr %prec U_PLUS
        | '!' expr
        | '~' expr
        | CLONE expr
        | expr '?' expr ':' expr
        | expr '?' ':' expr
        | get_value '{' expr '}'
        | expr '[' expr ']'
        | expr '[' ']' '=' expr
        | ID '(' expr_list ')'
        | get_value ID brackets
        | anon_function_expr                  /*! not supported */
        | NEW ID '(' expr_list ')'
        | NEW ID
        | NEW get_value ID
        | NEW get_value ID '(' expr_list ')'
        | NEW '(' expr ')'
        ;

expr_may_empty: expr
                | /* empty */
                ;

brackets: '(' expr_list ')'
        | brackets '(' expr_list ')'
        ;

id_list:  ID
        | id_list ',' ID
        ;

expr_list_not_e:  expr
                | expr_list_not_e ',' expr
                ;

expr_list: expr_list_not_e
	| /* empty */ 
        ;

const_decl_list_not_e:    ID '=' expr
                        | const_decl_list_not_e ',' ID '=' expr
                        ;

class_def: CLASS ID 
        |  CLASS ID EXTENDS ID
        |  CLASS ID IMPLEMENTS id_list
        |  CLASS ID EXTENDS ID IMPLEMENTS id_list
        ;

class_stmt_decl:  class_def '{' class_stmt_list '}'
                | FINAL class_def '{' class_stmt_list '}'
                | ABSTRACT class_def '{' class_stmt_list '}'
                ;

class_stmt_list: class_stmt_list_not_e
                | /* empty */
                ;

class_access_mod: PUBLIC
                | PROTECTED
                | PRIVATE
                | FINAL
                | ABSTRACT
                | READ_ONLY
                | STATIC
                ;

class_access_mod_list:    class_access_mod
                        | class_access_mod_list class_access_mod
                        ;

class_stmt_list_not_e:    class_stmt
                        | class_stmt_list_not_e class_stmt
                        ;

class_stmt: class_expr ';'
        |   class_access_mod_list function_stmt_decl
        |   USE id_list ';'
        |   class_stmt_decl
        ;

class_expr: class_access_mod_list get_value ID '=' expr
        |   class_access_mod_list get_value ID
        |   class_access_mod_list CONST const_decl_list_not_e ';'
        ;

interface_expr_def: INTERFACE ID 
                |   INTERFACE ID EXTENDS id_list
                ;

interface_stmt_decl: interface_expr_def '{' interface_stmt_list '}'
                ;

interface_stmt_list: interface_stmt_list_not_e
                |    /* empty */
                ;

interface_stmt_list_not_e: interface_stmt
                        |  interface_stmt_list_not_e interface_stmt
                        ;

interface_stmt: class_access_mod_list function_def ';' 
                ;

trait_stmt_decl: TRAIT ID  '{' class_stmt_list '}' 
                ;

function_def: FUNCTION ID '(' expr_func_list ')'
        |     FUNCTION ID '(' expr_func_list ')' ':' ID
        ;

function_stmt_decl: function_def '{' stmt_list '}' 
                ;

anon_function_expr: anon_function_stmt_decl /*! not supported */
                |   anon_function_short_stmt_decl /*! not supported */
                ;

expr_func_list:   expr_func_list_not_e
                | /* empty */
                ;

get_value_func:   '&' '$' ID
                | '$' ID
                | ID '&' '$' ID
                | ID '$' ID
                ;

get_value_func_list_not_e: get_value_func
                        |  get_value_func_list_not_e ',' get_value_func
                        ;

expr_func_list_not_e: get_value_func
                |     get_value_func '=' expr
                |     expr_func_list_not_e ',' get_value_func
                |     expr_func_list_not_e ',' get_value_func '=' expr
                ;

anon_function_def: FUNCTION '(' expr_func_list ')'
                |  FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'
                |  STATIC FUNCTION '(' expr_func_list ')'
                |  STATIC FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'
                |  FUNCTION '(' expr_func_list ')' ':' ID
                |  FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')' ':' ID
                |  STATIC FUNCTION '(' expr_func_list ')' ':' ID
                |  STATIC FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')' ':' ID
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