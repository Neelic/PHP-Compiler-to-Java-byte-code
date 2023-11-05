%{
#include <stdio.h>
extern int yylex();
void yyerror(char* str);
%}

%token START_CODE_PHP_TAG
%token END_CODE_PHP_TAG
%token HTML

%token ID
%token NUMBER
%token STRING
%token COM_STRING
%token CONST
%token RETURN
%token YIELD

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

%token CLASS
%token ABSTRACT
%token EXTENDS
%token IMPLEMENTS
%right PUBLIC PRIVATE PROTECTED FINAL STATIC READ_ONLY
%token INTERFACE
%token TRAIT

%right THROW
%left LOGIC_OR
%left LOGIC_XOR
%left LOGIC_AND
%left BOOLEAN_OR
%left BOOLEAN_AND
%nonassoc EQUAL EQUAL_STRICT
%right '?' ':'
%nonassoc '>' '<' EQU_MORE EQU_LESS
%left '|'
%left '&'
%left '^'
%right '='
%left SHIFT_L SHIFT_R
%left '-' '+' '.'
%left '/' '*' '%'
%right U_MINUS U_PLUS
%right POW
%right '!'
%right '~' INT_CAST FLOAT_CAST STRING_CAST ARRAY_CAST OBJECT_CAST BOOL_CAST
%left '['']' R_ARROW R_DOUBLE_ARROW QUARTER_DOT
%nonassoc '('')'

%nonassoc NEW CLONE

%%

start: top_stmt_list

top_stmt_list: top_stmt_list_not_e
                | /* empty */

top_stmt_list_not_e: top_stmt
                |    top_stmt_list_not_e top_stmt

top_stmt: stmt

get_value: '$'
        |  get_value '$'

get_value_func:   '&' '$' ID
                | '$' ID
                | ID '&' '$' ID
                | ID '$' ID

get_value_func_list_not_e: get_value_func
                        |  get_value_func_list_not_e ',' get_value_func

if_stmt:  IF '(' expr ')' stmt
        | IF '(' expr ')' stmt ELSE stmt
        | IF '(' expr ')' ':' stmt_list_may_empty END_IF ';'
        | IF '(' expr ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG END_IF ';'
        | IF '(' expr ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty ELSE ':' stmt_list_may_empty END_IF ';'
        | IF '(' expr ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty ELSE ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_IF ';'

switch_stmt: SWITCH '(' expr ')' '{' '}'
        |    SWITCH '(' expr ')' '{' case_default_stmt_list '}'
        |    SWITCH '(' expr ')' ':' case_default_stmt END_SWITCH ';'
        |    SWITCH '(' expr ')' ':' case_default_stmt END_CODE_PHP_TAG START_CODE_PHP_TAG case_default_stmt END_SWITCH ';'
        |    SWITCH '(' expr ')' ':' case_default_stmt END_CODE_PHP_TAG case_html_stmt_list START_CODE_PHP_TAG case_default_stmt END_SWITCH ';'

case_default_stmt_list:   case_default_stmt
                | case_default_stmt_list case_default_stmt

case_default_stmt: CASE expr ':' stmt_list_may_empty
        |  CASE expr ':' stmt_list_may_empty BREAK ';'
        |  DEFAULT ':' stmt_list_may_empty
        |  DEFAULT ':' stmt_list_may_empty BREAK ';'
        |  FINALLY '{' stmt_list_may_empty '}' 

case_html_stmt_list: START_CODE_PHP_TAG case_default_stmt_list END_CODE_PHP_TAG
                |    HTML
                |    case_html_stmt_list START_CODE_PHP_TAG case_default_stmt_list END_CODE_PHP_TAG
                |    case_html_stmt_list HTML

for_stmt: FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' stmt
        | FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' ':' stmt_list_may_empty END_FOR ';'
        | FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_FOR ';'

foreach_stmt: FOREACH '(' expr AS expr ')' stmt
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW get_value_func ID ')' stmt
        |     FOREACH '(' expr AS expr ')' ':' stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW get_value_func ID ')' ':' stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' expr AS expr ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' expr AS expr R_DOUBLE_ARROW get_value_func ID ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_FOREACH ';'

while_stmt: WHILE '(' expr ')' stmt
        |   WHILE '(' expr ')' ':' stmt_list_may_empty END_WHILE ';'
        |   WHILE '(' expr ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_WHILE ';'

do_while_stmt: DO stmt WHILE '(' expr ')' ';'

match_stmt: MATCH '(' expr ')' '{' match_stmt_list '}' ';'

match_stmt_list:  match_stmt_list_not_e
                | /* empty */

match_stmt_list_not_e:    match_arm 
                        | match_stmt_list_not_e ',' match_arm

match_arm: expr_list_not_e R_DOUBLE_ARROW expr
        |  DEFAULT R_DOUBLE_ARROW expr
        |  DEFAULT ',' R_DOUBLE_ARROW expr

try_stmt: TRY '{' stmt_list_may_empty '}'

try_catch_stmt:   try_stmt CATCH'(' ID '$' ID ')' '{' stmt_list_may_empty '}'
                | try_stmt CATCH'(' ID ')' '{' stmt_list_may_empty '}'
                | try_stmt

return_stmt: RETURN expr_may_empty ';'

yield_stmt: YIELD expr_may_empty ';'
        |   YIELD expr R_DOUBLE_ARROW expr ';'

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
        | function_stmt_decl
        | class_stmt_decl
        | interface_stmt_decl
        | trait_stmt_decl
        | THROW expr ';'
        | try_catch_stmt
        | match_stmt
        | CONST const_decl_list_not_e ';'
        | return_stmt
        | yield_stmt

static_var_list:  '$' ID
                | '$' ID '=' expr
                | static_var_list ',' '$' ID
                | static_var_list ',' '$' ID '=' expr

global_var_list:  get_value ID
                | global_var_list ',' get_value ID

stmt_list: stmt
	|  stmt_list stmt

stmt_list_may_empty: stmt_list
                |    /* empty */

php_code_section: START_CODE_PHP_TAG stmt_list_may_empty END_CODE_PHP_TAG   

html_php_stmt_list_not_e: HTML
                        | php_code_section
                        | html_php_stmt_list_not_e HTML
                        | html_php_stmt_list_not_e php_code_section

html_php_stmt_list: html_php_stmt_list_not_e
                |   /* empty */

expr:     NUMBER
        | STRING
        | COM_STRING
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
        | expr QUARTER_DOT ID
        | expr QUARTER_DOT get_value ID
        | expr QUARTER_DOT get_value '{' expr '}'
        | '(' expr ')'
        | expr '-' expr
        | expr '+' expr
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
        | ID '(' expr_list ')'
        | get_value ID branches
        | anon_function_expr
        | NEW ID '(' expr_list ')'
        | NEW ID
        | NEW get_value ID
        | NEW get_value ID '(' expr_list ')'
        | NEW '(' expr ')'

expr_may_empty: expr
                | /* empty */

branches: '(' expr_list ')'
        | branches '(' expr_list ')'

id_list:  ID
        | id_list ',' ID

expr_list_not_e:  expr
                | expr_list_not_e ',' expr

expr_list: expr_list_not_e
	| /* empty */ 

const_decl_list_not_e:    ID '=' expr
                        | const_decl_list_not_e ',' ID '=' expr

class_def: CLASS ID 
        |  CLASS ID EXTENDS ID
        |  CLASS ID IMPLEMENTS id_list
        |  CLASS ID EXTENDS ID IMPLEMENTS id_list

class_stmt_decl:  class_def '{' class_stmt_list '}'
                | class_access_mod class_def '{' class_stmt_list '}'

class_stmt_list: class_stmt_list_not_e
                | /* empty */

class_access_mod: PUBLIC
                | PROTECTED
                | PRIVATE
                | FINAL
                | ABSTRACT
                | READ_ONLY
                | STATIC

class_access_mod_list:    class_access_mod
                        | class_access_mod_list class_access_mod

class_stmt_list_not_e:    class_stmt
                        | class_stmt_list_not_e class_stmt

class_stmt: class_expr ';'
        |   class_access_mod_list function_stmt_decl
        |   USE id_list ';'
        |   class_stmt_decl

class_expr: class_access_mod_list get_value ID '=' expr
        |   class_access_mod_list get_value ID
        |   class_access_mod_list CONST const_decl_list_not_e ';'

interface_expr_def: INTERFACE ID 
                |   INTERFACE ID EXTENDS id_list

interface_stmt_decl: interface_expr_def '{' interface_stmt_list '}'

interface_stmt_list: interface_stmt_list_not_e
                |    /* empty */

interface_stmt_list_not_e: interface_stmt
                        |  interface_stmt_list_not_e interface_stmt

interface_stmt: class_access_mod_list function_def ';'

trait_expr_def: TRAIT ID 

trait_stmt_decl: trait_expr_def '{' class_stmt_list '}'

function_def: FUNCTION ID '(' expr_func_list ')'
        |     FUNCTION ID '(' expr_func_list ')' ':' ID

function_stmt_decl: function_def '{' stmt_list '}'

anon_function_expr: anon_function_stmt_decl
                |   anon_function_short_stmt_decl

expr_func_list:   expr_func_list_not_e
                | /* empty */

expr_func_list_not_e: get_value_func_list_not_e
                |     get_value_func ID '=' expr
                |     expr_func_list_not_e ',' get_value_func_list_not_e
                |     expr_func_list_not_e ',' get_value_func ID '=' expr

anon_function_def: FUNCTION '(' expr_func_list ')'
                |  FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'
                |  STATIC FUNCTION '(' expr_func_list ')'
                |  STATIC FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'
                |  FUNCTION '(' expr_func_list ')' ':' ID
                |  FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')' ':' ID
                |  STATIC FUNCTION '(' expr_func_list ')' ':' ID
                |  STATIC FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')' ':' ID

anon_function_stmt_decl: anon_function_def '{' stmt_list '}'

anon_function_short_def:  FN '(' expr_func_list ')'
                        | FN '(' expr_func_list ')' ':' ID
                        | STATIC FN '(' expr_func_list ')'
                        | STATIC FN '(' expr_func_list ')' ':' ID

anon_function_short_stmt_decl: anon_function_short_def R_DOUBLE_ARROW expr

%%

void yyerror(char* str) {
        fprintf(stderr, "ERROR: %s\n", str);
}