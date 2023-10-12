%{
#include <stdio.h>
%}

%token NUMBER STRING
%token CLASS EXTENDS IMPLEMENTS
%token ID FUNCTION
%token FOR WHILE DO IF ELSE

%right '='
%left '-' '+' '/' '*'
%left '/' '*'
%right U_MINUS U_PLUS
%right '!'
%left '.' '['']' R_ARROW
%left '>' '<'
%nonassoc '('')' 

%%

bool_op: '>' /* TODO Доделать как-то логические операции */
        | '<'

get_value: '$'
        | get_value '$'

if_stmt: IF '(' expr ')' stmt
        | IF '(' expr ')' stmt ELSE stmt

for_stmt: FOR '(' expr ';' expr ';' expr ')' stmt

while_stmt: WHILE '(' expr ')' stmt
        | WHILE '(' ID ')' stmt

do_while_stmt: DO stmt WHILE '(' expr ')' ';'
                | DO stmt WHILE '(' ID ')' ';'

stmt: expr';' 
        | if_stmt
        | '{'stmt_list'}'
        | ';'
        | while_stmt
        | do_while_stmt

expr: NUMBER
        | STRING
        | ID
        | get_value ID
        | expr'='expr
        | expr'['expr']'
        | expr'-'expr
        | expr'+'expr
        | expr'*'expr
        | expr'/'expr
        | expr'%'expr
        | '-'expr %prec U_MINUS
        | '+'expr %prec U_PLUS
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

stmt_list: stmt
	| stmt_list stmt

class_def: CLASS ID 
        | CLASS ID EXTENDS ID
        | CLASS ID IMPLEMENTS ID
        | CLASS ID IMPLEMENTS id_list /* TODO конфликт с expr */

class_stmt: class_def

id_list: ID
        | id_list ',' ID

param_list: param_list_not_e
        | /* empty */

param_list_not_e: get_value ID
                | param_list_not_e ',' get_value ID

function_def: FUNCTION ID '(' param_list ')'

function_stmt: function_def '{' stmt_list '}'

%%

/* int main(int argc, char** argv) {
        return yyparse();
} */

void yyerror(char* str) {
        fprintf(stderr, "ERROR: %s\n", str);
}