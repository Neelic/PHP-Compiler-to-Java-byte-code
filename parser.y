%{
#include <stdio.h>
%}

%token START_CODE_PHP_TAG
%token END_CODE_PHP_TAG
%token HTML

%token R_ARROW
%token R_ARROW_O
%token QUARTER_DOT

%token ID
%token NUMBER
%token STRING

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
%token STATIC
%token GLOBAL

%token CLASS
%token ABSTRACT
%token EXTENDS
%token IMPLEMENTS
%token PUBLIC
%token PRIVATE
%token PROTECTED
%token INTERFACE
%token TRAIT

%right '='
%left '-' '+' '.'
%left '/' '*' '%'
%right U_MINUS U_PLUS
%left '>' '<' EQU_MORE EQU_LESS EQUAL EQUAL_STRICT
%right '!'
%left '['']' R_ARROW R_ARROW_O QUARTER_DOT
%nonassoc '('')'

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

get_value_func_list_not_e: get_value_func
                        |  get_value_func_list_not_e ',' get_value_func

if_stmt:  IF '(' expr_or_const ')' stmt
        | IF '(' expr_or_const ')' stmt ELSE stmt
        | IF '(' expr_or_const ')' ':' stmt_list_may_empty END_IF ';'
        | IF '(' expr_or_const ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG END_IF ';'
        | IF '(' expr_or_const ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty ELSE ':' stmt_list_may_empty END_IF ';'
        | IF '(' expr_or_const ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty ELSE ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_IF ';'

switch_stmt: SWITCH '(' expr_or_const ')' '{' '}'
        |    SWITCH '(' expr_or_const ')' '{' case_default_stmt_list '}'
        |    SWITCH '(' expr_or_const ')' ':' case_default_stmt END_SWITCH ';'
        |    SWITCH '(' expr_or_const ')' ':' case_default_stmt END_CODE_PHP_TAG START_CODE_PHP_TAG case_default_stmt END_SWITCH ';'
        |    SWITCH '(' expr_or_const ')' ':' case_default_stmt END_CODE_PHP_TAG case_html_stmt_list START_CODE_PHP_TAG case_default_stmt END_SWITCH ';'

case_default_stmt_list:   case_default_stmt
                | case_default_stmt_list case_default_stmt

case_default_stmt: CASE expr_or_const ':' stmt_list_may_empty
        |  CASE expr_or_const ':' stmt_list_may_empty BREAK ';'
        |  DEFAULT ':' stmt_list_may_empty
        |  DEFAULT ':' stmt_list_may_empty BREAK ';'

case_html_stmt_list: START_CODE_PHP_TAG case_default_stmt_list END_CODE_PHP_TAG
                |    HTML
                |    case_html_stmt_list START_CODE_PHP_TAG case_default_stmt_list END_CODE_PHP_TAG
                |    case_html_stmt_list HTML

for_stmt: FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' stmt
        | FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' ':' stmt_list_may_empty END_FOR ';'
        | FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_FOR ';'

foreach_stmt: FOREACH '(' var_expr AS var_expr ')' stmt
        |     FOREACH '(' var_expr AS var_expr R_ARROW_O get_value_func ID ')' stmt
        |     FOREACH '(' var_expr AS var_expr ')' ':' stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' var_expr AS var_expr R_ARROW_O get_value_func ID ')' ':' stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' var_expr AS var_expr ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' var_expr AS var_expr R_ARROW_O get_value_func ID ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_FOREACH ';'

while_stmt: WHILE '(' expr_or_const ')' stmt
        |   WHILE '(' expr_or_const ')' ':' stmt_list_may_empty END_WHILE ';'
        |   WHILE '(' expr_or_const ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_WHILE ';'

do_while_stmt: DO stmt WHILE '(' expr_or_const ')' ';'

stmt:     simple_stmt
        | if_stmt
        | switch_stmt
        | '{'stmt_list'}'
        | ';'
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

static_var_list:  '$' ID
                | '$' ID '=' expr
                | static_var_list ',' '$' ID
                | static_var_list ',' '$' ID '=' expr

global_var_list:  get_value ID
                | global_var_list ',' get_value ID

simple_stmt: expr ';'
        |    ID ';'

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
        | var_expr
        | var_expr '=' expr_or_const
        | expr_or_const '-' expr_or_const
        | expr_or_const '+' expr_or_const
        | expr_or_const '*' expr_or_const
        | expr_or_const '/' expr_or_const
        | expr_or_const '%' expr_or_const
        | expr_or_const '>' expr_or_const
        | expr_or_const '<' expr_or_const
        | expr_or_const EQUAL expr_or_const 
        | expr_or_const EQUAL_STRICT expr_or_const
        | expr_or_const EQU_MORE expr_or_const
        | expr_or_const EQU_LESS expr_or_const
        | '-' expr_or_const %prec U_MINUS
        | '+' expr_or_const %prec U_PLUS
        | '!' expr_or_const
        | anon_function_expr

expr_or_const: expr
        |   ID

expr_may_empty: expr
                | /* empty */

var_expr: callable_var
        | '(' expr ')'
        | string_expr
        | var_expr R_ARROW ID
        | var_expr R_ARROW var_expr
        | var_expr QUARTER_DOT ID
        | var_expr QUARTER_DOT var_expr

callable_var:     get_value ID
                | get_value '{' expr '}'
                | var_expr '[' expr ']'
                | function_call_expr

string_expr: STRING
        |    string_expr '.' STRING
        |    string_expr '.' ID
        |    ID '.' string_expr

id_list:  ID
        | id_list ',' ID

expr_list_not_e:  expr
                | expr_list_not_e ',' expr

expr_list: expr_list_not_e
	| /* empty */ 

class_expr_def:   CLASS ID 
                | CLASS ID EXTENDS ID
                | CLASS ID IMPLEMENTS id_list
                | CLASS ID EXTENDS ID IMPLEMENTS id_list

class_stmt_decl:  class_expr_def '{' class_stmt_list '}'
                | abstract_class_def '{' abstract_class_stmt_list '}'

class_stmt_list: class_stmt_list_not_e
                | /* empty */

class_expr_visibility:    PUBLIC
                        | PRIVATE
                        | PROTECTED
                        | PUBLIC STATIC
                        | PRIVATE STATIC
                        | PROTECTED STATIC
                        | STATIC PUBLIC
                        | STATIC PRIVATE
                        | STATIC PROTECTED

class_stmt_list_not_e:    class_stmt
                        | class_stmt_list_not_e class_stmt

class_stmt: class_expr ';'
        |   class_expr_visibility function_stmt_decl
        |   USE id_list ';'
        |   class_stmt_decl

class_expr: class_expr_visibility get_value ID '=' expr_or_const
        |   class_expr_visibility get_value ID

abstract_class_def: ABSTRACT class_expr_def

abstract_class_stmt_list: abstract_class_stmt_list_not_e
                        | /* empty */

abstract_class_stmt_list_not_e:   class_stmt
                                | abstract_class_stmt
                                | abstract_class_stmt_list_not_e class_stmt
                                | abstract_class_stmt_list_not_e abstract_class_stmt

abstract_class_expr_visibility:   class_expr_visibility ABSTRACT
                                | PUBLIC ABSTRACT STATIC
                                | PRIVATE ABSTRACT STATIC
                                | PROTECTED ABSTRACT STATIC
                                | STATIC ABSTRACT PUBLIC
                                | STATIC ABSTRACT PRIVATE
                                | STATIC ABSTRACT PROTECTED
                                | ABSTRACT class_expr_visibility

abstract_class_expr: abstract_class_expr_visibility get_value ID '=' expr
                |    abstract_class_expr_visibility get_value ID '=' ID
                |    abstract_class_expr_visibility get_value ID

abstract_class_stmt: abstract_class_expr_visibility function_def ';'
                |    abstract_class_expr_visibility anon_function_expr ';'
                |    abstract_class_expr ';'

interface_expr_def: INTERFACE ID 
                |   INTERFACE ID EXTENDS id_list

interface_stmt_decl: interface_expr_def '{' interface_stmt_list '}'

interface_stmt_list: interface_stmt_list_not_e
                |    /* empty */

interface_stmt_list_not_e: interface_stmt
                        |  interface_stmt_list_not_e interface_stmt

interface_stmt: class_expr_visibility function_def ';'

trait_expr_def: TRAIT ID 

trait_stmt_decl: trait_expr_def '{' abstract_class_stmt_list '}'

function_call_expr: ID '(' expr_list ')'
                |   get_value ID branches

branches: '(' expr_list ')'
        | branches '(' expr_list ')'

function_def: FUNCTION ID '(' expr_func_list ')'

function_stmt_decl: function_def '{' stmt_list '}'
                |   anon_function_expr ';'

anon_function_expr: anon_function_stmt_decl
                |   anon_function_short_stmt_decl

expr_func_list:   expr_func_list_not_e
                | /* empty */

expr_func_list_not_e: get_value_func_list_not_e
                |     get_value_func ID '=' expr_or_const
                |     expr_func_list_not_e ',' get_value_func_list_not_e
                |     expr_func_list_not_e ',' get_value_func ID '=' expr_or_const

anon_function_def: FUNCTION '(' expr_func_list ')'
                |  FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'
                |  STATIC FUNCTION '(' expr_func_list ')'
                |  STATIC FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'

anon_function_stmt_decl: anon_function_def '{' stmt_list '}'

anon_function_short_def:  FN '(' expr_func_list ')'
                        | STATIC FN '(' expr_func_list ')'

anon_function_short_stmt_decl: anon_function_short_def R_ARROW_O expr_or_const

%%

int main(int argc, char** argv) {
        return yyparse();
}

void yyerror(char* str) {
        fprintf(stderr, "ERROR: %s\n", str);
}