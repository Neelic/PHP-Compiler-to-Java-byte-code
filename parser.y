%{
#include <stdio.h>
%}

%token R_ARROW

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
%token USE

%token CLASS
%token ABSTRACT
%token EXTENDS
%token IMPLEMENTS
%token PUBLIC
%token PRIVATE
%token PROTECTED
%token STATIC

%right '='
%left '-' '+'
%left '/' '*' '%'
%right U_MINUS U_PLUS
%right '!'
%left '.' '['']' R_ARROW
%left '>' '<'
%nonassoc '('')'

%%

start: top_stmt_list

top_stmt_list: top_stmt_list_ex

top_stmt_list_ex: top_stmt_list_ex top_stmt
                | /* empty */

top_stmt: stmt

get_value: '$'
        |  get_value '$'

if_stmt: IF '(' expr ')' stmt
        | IF '(' expr ')' stmt ELSE stmt

for_stmt: FOR '(' expr ';' expr ';' expr ')' stmt

foreach_stmt: FOREACH '(' expr AS expr ')' stmt
        | FOREACH '(' expr AS expr '=' '>' expr ')' stmt

while_stmt: WHILE '(' expr ')' stmt

do_while_stmt: DO stmt WHILE '(' expr ')' ';'

stmt:     expr';'
        | ID ';'
        | if_stmt
        | '{'stmt_list'}'
        | ';'
        | while_stmt
        | do_while_stmt
        | for_stmt
        | foreach_stmt
        | function_stmt_decl
        | class_stmt_decl

expr:     NUMBER
        | string_expr
        | get_value ID
        | expr '=' expr
        | expr '[' expr ']'
        | expr '-' expr
        | expr '+' expr
        | expr '*' expr
        | expr '/' expr
        | expr '%' expr
        | '-'expr %prec U_MINUS
        | '+'expr %prec U_PLUS
        | expr '=' ID
        | expr '-' ID
        | expr '+' ID
        | expr '*' ID
        | expr '/' ID
        | expr '%' ID
        | ID'('expr_list')'
        | expr R_ARROW get_value ID %prec R_ARROW

string_expr: STRING
        |    string_expr '.' STRING
        |    string_expr '.' ID
        |    ID '.' string_expr

id_list:  ID ',' ID
        | id_list ',' ID

expr_list_not_e:  expr
	        | expr_list','expr

expr_list: expr_list_not_e
	| /* empty */ 

class_expr_def:   CLASS ID 
                | CLASS ID EXTENDS ID
                | CLASS ID IMPLEMENTS ID
                | CLASS ID IMPLEMENTS id_list
                | CLASS ID EXTENDS ID IMPLEMENTS ID
                | CLASS ID EXTENDS ID IMPLEMENTS id_list

abstract_class_def: ABSTRACT CLASS ID 
                |   ABSTRACT CLASS ID EXTENDS ID
                |   ABSTRACT CLASS ID IMPLEMENTS ID
                |   ABSTRACT CLASS ID IMPLEMENTS id_list
                |   ABSTRACT CLASS ID EXTENDS ID IMPLEMENTS ID
                |   ABSTRACT CLASS ID EXTENDS ID IMPLEMENTS id_list

class_stmt_decl:  class_expr_def '{' class_stmt_list '}'
                | abstract_class_def '{' abstract_class_stmt_list '}'

class_stmt_list: class_stmt_list_not_e
                | /* empty */

abstract_class_stmt_list: abstract_class_stmt_list_not_e
                        | /* empty */

abstract_class_stmt_list_not_e:   class_stmt
                                | abstract_class_stmt
                                | abstract_class_stmt_list_not_e class_stmt
                                | abstract_class_stmt_list_not_e abstract_class_stmt

class_expr_visibility:    PUBLIC
                        | PRIVATE
                        | PROTECTED
                        | PUBLIC STATIC
                        | PRIVATE STATIC
                        | PROTECTED STATIC
                        | STATIC PUBLIC
                        | STATIC PRIVATE
                        | STATIC PROTECTED

abstract_class_expr_visibility:   class_expr_visibility ABSTRACT
                                | PUBLIC ABSTRACT STATIC
                                | PRIVATE ABSTRACT STATIC
                                | PROTECTED ABSTRACT STATIC
                                | STATIC ABSTRACT PUBLIC
                                | STATIC ABSTRACT PRIVATE
                                | STATIC ABSTRACT PROTECTED
                                | ABSTRACT class_expr_visibility

class_stmt_list_not_e:    class_stmt
                        | class_stmt_list_not_e class_stmt

class_stmt: class_expr ';'
        |   class_expr_visibility function_stmt_decl
        |   USE ID ';'
        |   class_stmt_decl

abstract_class_stmt: abstract_class_expr_visibility function_def ';'
                |    abstract_class_expr_visibility anon_function_stmt_decl

class_expr: class_expr_visibility get_value ID '=' expr
        |   class_expr_visibility get_value ID '=' ID

stmt_list: stmt
	|  stmt_list stmt

function_def: FUNCTION ID '(' expr_list ')'

function_stmt_decl: function_def '{' stmt_list '}'

anon_function_def: get_value ID '=' FUNCTION '(' expr_list ')'
                |  get_value ID '=' FUNCTION '(' expr_list ')' USE '(' get_value ID ')'
                |  get_value ID '=' STATIC FUNCTION '(' expr_list ')'
                |  get_value ID '=' STATIC FUNCTION '(' expr_list ')' USE '(' get_value ID ')'

anon_function_stmt_decl: anon_function_def '{' stmt_list '}' ';'

%%

int main(int argc, char** argv) {
        return yyparse();
}

void yyerror(char* str) {
        fprintf(stderr, "ERROR: %s\n", str);
}