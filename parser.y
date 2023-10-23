%{
#include <stdio.h>
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
%right PUBLIC PRIVATE PROTECTED FINAL STATIC
%token INTERFACE
%token TRAIT

%right THROW
%left LOGIC_OR
%left LOGIC_XOR
%left LOGIC_AND
%left BOOLEAN_OR
%left BOOLEAN_AND
%nonassoc EQUAL EQUAL_STRICT
%left '?' ':'
%nonassoc '>' '<' EQU_MORE EQU_LESS
%left '|'
%left '&'
%left '^'
%right '='
%left SHIFT_L SHIFT_R
%left '-' '+' '.'
%left '/' '*' '%'
%right U_MINUS U_PLUS
%right '!'
%right '~'
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
        |  FINALLY '{' stmt_list_may_empty '}' 

case_html_stmt_list: START_CODE_PHP_TAG case_default_stmt_list END_CODE_PHP_TAG
                |    HTML
                |    case_html_stmt_list START_CODE_PHP_TAG case_default_stmt_list END_CODE_PHP_TAG
                |    case_html_stmt_list HTML

for_stmt: FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' stmt
        | FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' ':' stmt_list_may_empty END_FOR ';'
        | FOR '(' expr_may_empty ';' expr_may_empty ';' expr_may_empty ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_FOR ';'

foreach_stmt: FOREACH '(' var_expr AS callable_var ')' stmt
        |     FOREACH '(' var_expr AS callable_var R_DOUBLE_ARROW get_value_func ID ')' stmt
        |     FOREACH '(' var_expr AS callable_var ')' ':' stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' var_expr AS callable_var R_DOUBLE_ARROW get_value_func ID ')' ':' stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' var_expr AS callable_var ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_FOREACH ';'
        |     FOREACH '(' var_expr AS callable_var R_DOUBLE_ARROW get_value_func ID ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_FOREACH ';'

while_stmt: WHILE '(' expr_or_const ')' stmt
        |   WHILE '(' expr_or_const ')' ':' stmt_list_may_empty END_WHILE ';'
        |   WHILE '(' expr_or_const ')' ':' stmt_list_may_empty END_CODE_PHP_TAG html_php_stmt_list START_CODE_PHP_TAG stmt_list_may_empty END_WHILE ';'

do_while_stmt: DO stmt WHILE '(' expr_or_const ')' ';'

match_stmt: MATCH '(' expr_or_const ')' '{' match_stmt_list '}' ';'

match_stmt_list:  match_stmt_list_not_e
                | /* empty */

match_stmt_list_not_e:    match_arm 
                        | match_stmt_list_not_e ',' match_arm

match_arm: expr_or_const_list_not_e R_DOUBLE_ARROW expr_or_const
        |  DEFAULT R_DOUBLE_ARROW expr_or_const
        |  DEFAULT ',' R_DOUBLE_ARROW expr_or_const

try_stmt: TRY '{' stmt_list_may_empty '}'

try_catch_stmt:   try_stmt CATCH'(' ID '$' ID ')' '{' stmt_list_may_empty '}'
                | try_stmt CATCH'(' ID ')' '{' stmt_list_may_empty '}'
                | try_stmt

return_stmt: RETURN expr_or_const ';'
        |    RETURN ';'

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
        | THROW expr ';'
        | try_catch_stmt
        | match_stmt
        | CONST const_decl_list_not_e ';'
        | return_stmt

static_var_list:  '$' ID
                | '$' ID '=' expr_or_const
                | static_var_list ',' '$' ID
                | static_var_list ',' '$' ID '=' expr_or_const

global_var_list:  get_value ID
                | global_var_list ',' get_value ID

simple_stmt: expr_or_const ';'

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
        | var_expr
        | var_expr '=' expr_or_const
        | var_expr '=' '&' var_expr
        | '(' expr ')'
        | '(' expr ')' R_ARROW ID
        | '(' expr ')' R_ARROW var_expr
        | '(' expr ')' QUARTER_DOT ID
        | '(' expr ')' QUARTER_DOT var_expr
        | expr_or_const '-' expr_or_const
        | expr_or_const '+' expr_or_const
        | expr_or_const '*' expr_or_const
        | expr_or_const '/' expr_or_const
        | expr_or_const '%' expr_or_const
        | expr_or_const '.' expr_or_const
        | expr_or_const '>' expr_or_const
        | expr_or_const '<' expr_or_const
        | expr_or_const BOOLEAN_OR expr_or_const
        | expr_or_const BOOLEAN_AND expr_or_const
        | expr_or_const LOGIC_OR expr_or_const
        | expr_or_const LOGIC_XOR expr_or_const
        | expr_or_const LOGIC_AND expr_or_const
        | expr_or_const EQUAL expr_or_const 
        | expr_or_const EQUAL_STRICT expr_or_const
        | expr_or_const EQU_MORE expr_or_const
        | expr_or_const EQU_LESS expr_or_const
        | expr_or_const SHIFT_L expr_or_const
        | expr_or_const SHIFT_R expr_or_const
        | expr_or_const '^' expr_or_const
        | expr_or_const '|' expr_or_const
        | expr_or_const '&' expr_or_const
        | '-' expr_or_const %prec U_MINUS
        | '+' expr_or_const %prec U_PLUS
        | '!' expr_or_const
        | '~' expr_or_const
        | anon_function_expr
        | CLONE expr_or_const
        | expr_or_const '?' expr_or_const ':' expr_or_const
        | expr '?' ':' expr_or_const
        | new_expr

expr_or_const:    expr
                | ID

expr_or_const_list_not_e: expr_or_const
                        | expr_or_const_list_not_e ',' expr_or_const

expr_may_empty: expr
                | /* empty */

var_expr: callable_var
        | var_expr R_ARROW ID
        | var_expr R_ARROW var_expr
        | var_expr QUARTER_DOT ID
        | var_expr QUARTER_DOT var_expr

callable_var:     get_value ID
                | get_value '{' expr '}'
                | var_expr '[' expr ']'
                | function_call_expr

id_list:  ID
        | id_list ',' ID

expr_list_not_e:  expr
                | expr_list_not_e ',' expr

expr_list: expr_list_not_e
	| /* empty */ 

const_decl_expr: ID '=' expr 

const_decl_list_not_e:    const_decl_expr
                        | const_decl_list_not_e ',' const_decl_expr

new_expr: NEW ID '(' expr_list ')'
        | NEW ID
        | NEW get_value ID
        | NEW get_value ID '(' expr_list ')'
        | NEW '(' expr ')'

class_expr_def:   CLASS ID 
                | CLASS ID EXTENDS ID
                | CLASS ID IMPLEMENTS id_list
                | CLASS ID EXTENDS ID IMPLEMENTS id_list

class_stmt_decl:  class_expr_def '{' class_stmt_list '}'
                | abstract_class_def '{' abstract_class_stmt_list '}'

class_stmt_list: class_stmt_list_not_e
                | /* empty */

class_access_mod: PUBLIC
                | PROTECTED
                | PRIVATE

class_expr_visibility:    class_access_mod
                        | class_access_mod STATIC
                        | STATIC class_access_mod
                        | FINAL class_access_mod 
                        | class_access_mod FINAL
                        | STATIC class_access_mod FINAL
                        | STATIC FINAL class_access_mod 
                        | FINAL STATIC class_access_mod
                        | FINAL class_access_mod STATIC
                        | class_access_mod STATIC FINAL
                        | class_access_mod FINAL STATIC

class_stmt_list_not_e:    class_stmt
                        | class_stmt_list_not_e class_stmt

class_stmt: class_expr ';'
        |   class_expr_visibility function_stmt_decl
        |   USE id_list ';'
        |   class_stmt_decl

class_expr: class_expr_visibility get_value ID '=' expr_or_const
        |   class_expr_visibility get_value ID
        |   class_expr_visibility CONST const_decl_list_not_e ';'

abstract_class_def: ABSTRACT class_expr_def

abstract_class_stmt_list: abstract_class_stmt_list_not_e
                        | /* empty */

abstract_class_stmt_list_not_e:   class_stmt
                                | abstract_class_stmt
                                | abstract_class_stmt_list_not_e class_stmt
                                | abstract_class_stmt_list_not_e abstract_class_stmt

abstract_class_expr_visibility:   class_expr_visibility ABSTRACT
                                | class_access_mod ABSTRACT STATIC
                                | class_access_mod ABSTRACT STATIC FINAL
                                | class_access_mod ABSTRACT FINAL STATIC
                                | STATIC ABSTRACT class_access_mod
                                | STATIC ABSTRACT FINAL class_access_mod
                                | FINAL ABSTRACT STATIC class_access_mod
                                | STATIC FINAL ABSTRACT class_access_mod
                                | FINAL STATIC ABSTRACT class_access_mod
                                | ABSTRACT class_expr_visibility

abstract_class_expr: abstract_class_expr_visibility get_value ID '=' expr
                |    abstract_class_expr_visibility get_value ID '=' ID
                |    abstract_class_expr_visibility get_value ID
                |    abstract_class_expr_visibility CONST const_decl_list_not_e ';'

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

anon_function_short_stmt_decl: anon_function_short_def R_DOUBLE_ARROW expr_or_const

%%

int main(int argc, char** argv) {
        return yyparse();
}

void yyerror(char* str) {
        fprintf(stderr, "ERROR: %s\n", str);
}