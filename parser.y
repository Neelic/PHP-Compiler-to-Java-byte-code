%{
#include <stdio.h>
%}

%token NUMBER STRING
%token CLASS EXTENDS IMPLEMENTS
%token ID FUNCTION
%token FOR WHILE DO IF ELSE FOREACH AS

%nonassoc ID
%right '='
%left '-' '+'
%left '/' '*' '%'
%right U_MINUS U_PLUS
%right '!'
%left '.' '['']' R_ARROW
%left '>' '<'
%nonassoc '('')' CLASS_DECL

%%

start: top_stmt_list

top_stmt_list: top_stmt_list_ex

top_stmt_list_ex: top_stmt_list_ex top_stmt
                | /* empty */

top_stmt: stmt
        | function_stmt_decl
        | class_stmt_decl

bool_op: '>' /* TODO Доделать как-то логические операции */
        | '<'

get_value: '$'
        | get_value '$'

if_stmt: IF '(' expr ')' stmt
        | IF '(' expr ')' stmt ELSE stmt

for_stmt: FOR '(' expr ';' expr ';' expr ')' stmt

foreach_stmt: FOREACH '(' expr AS expr ')' stmt
        | FOREACH '(' expr AS expr '=' '>' expr ')' stmt

while_stmt: WHILE '(' expr ')' stmt

do_while_stmt: DO stmt WHILE '(' expr ')' ';'

stmt: expr';'
        | ID ';'
        | if_stmt
        | '{'stmt_list'}'
        | ';'
        | while_stmt
        | do_while_stmt

expr: NUMBER
        | string_expr
        | get_value ID
        | expr'='expr
        | expr'['expr']'
        | expr'-' expr
        | expr'+' expr
        | expr'*' expr
        | expr'/' expr
        | expr'%' expr
        | '-'expr %prec U_MINUS
        | '+'expr %prec U_PLUS
        | expr '=' ID
        | expr '-' ID
        | expr '+' ID
        | expr '*' ID
        | expr '/' ID
        | expr '%' ID
        | '-' expr %prec U_MINUS
        | '+' expr %prec U_PLUS
        | ID'('expr_list')'
        | expr '-' '>' get_value ID %prec R_ARROW
        | expr bool_op expr /* TODO исправить конфликт с круглыми скобками */
        | '!' expr
        | expr bool_op expr
        | expr '|' '|' expr
        | expr '&' '&' expr

expr_list_not_e: expr
	| expr_list','expr

expr_list: expr_list_not_e
	| /* empty */ 

string_expr: STRING
        | string_expr '.' STRING
        | string_expr '.' ID
        | ID '.' string_expr

stmt_list: stmt
	| stmt_list stmt

class_def: CLASS ID %prec CLASS_DECL
        | CLASS ID EXTENDS ID %prec CLASS_DECL
        | CLASS ID IMPLEMENTS ID %prec CLASS_DECL
        | CLASS ID IMPLEMENTS id_list %prec CLASS_DECL

class_stmt_decl: class_def '{' class_stmt_list '}'

class_stmt_list: class_stmt_list_not_e
                | /* empty */

class_stmt_list_not_e:

id_list: ID ',' ID
        | id_list ',' ID

function_def: FUNCTION ID '(' expr_list ')'

function_stmt_decl: function_def '{' stmt_list '}'

%%

int main(int argc, char** argv) {
        return yyparse();
}

void yyerror(char* str) {
        fprintf(stderr, "ERROR: %s\n", str);
}