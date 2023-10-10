%{  
%}

%token NUMBER STRING BOOL_OP
%token CLASS EXTENDS IMPLEMENTS
%token ID FUNCTION
%token FOR WHILE DO IF

%right '='
%left '-' '+' '/' '*'
%left '.' '['']'
%right U_MINUS
%nonassoc '('')' 

%%

get_value: '$'
        | get_value '$'

decl_var: get_value ID '=' NUMBER
        | get_value ID '=' STRING
        | get_value ID '=' ID
        | get_value ID '=' get_value ID

bool_stmt: get_value ID BOOL_OP get_value ID
        | '(' get_value ID BOOL_OP get_value ID ')'
        | bool_stmt BOOL_OP get_value ID
        | bool_stmt BOOL_OP bool_stmt

if_stmt: IF '(' bool_stmt ')' stmt
        | IF '(' get_value ID ')' stmt
        | IF '(' ID ')' stmt
        | IF '(' decl_var ')' stmt

for_stmt: FOR '(' expr ';' expr ';' expr ')' stmt
	| FOR '(' decl_var ';' expr ';' expr ')' stmt

while_stmt: WHILE '(' bool_stmt ')' stmt
        | WHILE '(' get_value ID ')' stmt
        | WHILE '(' ID ')' stmt
        | WHILE '(' decl_var ')' stmt

do_while_stmt: DO stmt WHILE '(' bool_stmt ')' ';'

stmt: expr';' 
        | if_stmt
        | '{'stmt_list'}'
        | ';'
        | while_stmt

expr: NUMBER
        | ID
        | STRING
        | expr'='expr
        | expr'['expr']'
        | expr'-'expr
        | '-'expr %prec U_MINUS
        | ID'('expr_list')'
        | expr'.'ID

expr_list: expr
	| expr_list','expr

expr_list_e: expr_list
	   | /* empty */

stmt_list: stmt
	| stmt_list stmt

class_def: CLASS ID 
        | CLASS ID EXTENDS ID
        | CLASS ID IMPLEMENTS id_list

id_list: ID
        | id_list ',' ID

function_def: FUNCTION ID '(' function_arg_list ')'

function_arg_list:

%%

int main() {
        return yyparse();
}