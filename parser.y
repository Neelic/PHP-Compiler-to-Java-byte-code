%{
#include <stdio.h>
%}

%token START_CODE_PHP_TAG
%token END_CODE_PHP_TAG

%token R_ARROW
%token R_ARROW_O
%token QUARTER_DOT

%token ID
%token NUMBER
%token STRING

%token FOR
%token WHILE
%token DO
%token FOREACH
%token AS

%token IF
%token ELSE

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

%right '='
%left '-' '+' '.'
%left '/' '*' '%'
%right U_MINUS U_PLUS
%left '>' '<'
%right '!'
%left '['']' R_ARROW R_ARROW_O QUARTER_DOT
%nonassoc '('')'

%%

start: top_stmt_list

top_stmt_list: top_stmt_list_not_e
                | /* empty */

top_stmt_list_not_e: top_stmt
                |    top_stmt_list_not_e top_stmt

top_stmt: START_CODE_PHP_TAG stmt_list END_CODE_PHP_TAG

get_value: '$'
        |  get_value '$'

get_value_func:   '&' '$' ID
                | '$' ID

get_value_func_list_not_e: get_value_func
                        |  get_value_func_list_not_e ',' get_value_func

if_stmt:  IF '(' expr ')' stmt
        | IF '(' expr ')' stmt ELSE stmt

for_stmt: FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' stmt

foreach_stmt: FOREACH '(' var_expr AS var_expr ')' stmt
        |     FOREACH '(' var_expr AS var_expr R_ARROW_O get_value_func ID ')' stmt

while_stmt: WHILE '(' expr ')' stmt

do_while_stmt: DO stmt WHILE '(' expr ')' ';'

stmt:     simple_stmt
        | if_stmt
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

expr:     NUMBER
        | var_expr
        | var_expr '=' expr
        | expr '-' expr
        | expr '+' expr
        | expr '*' expr
        | expr '/' expr
        | expr '%' expr
        | expr '>' expr
        | expr '<' expr
        | var_expr '=' ID
        | expr '-' ID
        | expr '+' ID
        | expr '*' ID
        | expr '/' ID
        | expr '%' ID
        | expr '>' ID
        | expr '<' ID
        | ID '-' expr
        | ID '+' expr
        | ID '*' expr
        | ID '/' expr
        | ID '%' expr
        | ID '>' expr
        | ID '<' expr
        | '-' expr %prec U_MINUS
        | '+' expr %prec U_PLUS
        | '-' ID %prec U_MINUS
        | '+' ID %prec U_MINUS
        | anon_function_expr

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

id_list:  ID ',' ID
        | id_list ',' ID

expr_list_not_e:  expr
	        | expr_list_not_e ',' expr

expr_list: expr_list_not_e
	| /* empty */ 

class_expr_def:   CLASS ID 
                | CLASS ID EXTENDS ID
                | CLASS ID IMPLEMENTS ID
                | CLASS ID IMPLEMENTS id_list
                | CLASS ID EXTENDS ID IMPLEMENTS ID
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
        |   USE ID ';'
        |   USE id_list ';'
        |   class_stmt_decl

class_expr: class_expr_visibility get_value ID '=' expr
        |   class_expr_visibility get_value ID '=' ID
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
                |    abstract_class_expr_visibility anon_function_stmt_decl
                |    abstract_class_expr ';'

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
                |     get_value_func ID '=' ID
                |     get_value_func ID '=' expr
                |     expr_func_list_not_e ',' get_value_func_list_not_e
                |     expr_func_list_not_e ',' get_value_func ID '=' ID
                |     expr_func_list_not_e ',' get_value_func ID '=' expr

anon_function_def: FUNCTION '(' expr_func_list ')'
                |  FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'
                |  STATIC FUNCTION '(' expr_func_list ')'
                |  STATIC FUNCTION '(' expr_func_list ')' USE '(' get_value_func_list_not_e ')'

anon_function_stmt_decl: anon_function_def '{' stmt_list '}'

anon_function_short_def:  FN '(' expr_func_list ')'
                        | STATIC FN '(' expr_func_list ')'

anon_function_short_stmt_decl: anon_function_short_def R_ARROW_O expr

%%

int main(int argc, char** argv) {
        return yyparse();
}

void yyerror(char* str) {
        fprintf(stderr, "ERROR: %s\n", str);
}