%{  
%}

%token CLASS EXTENDS IMPLEMENTS
%token ID FUNCTION

%%

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