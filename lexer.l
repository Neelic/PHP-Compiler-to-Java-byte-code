%{
#include <stdio.h>
int yyerror(char* errormsg);
%}

%%
%%

int main(void) {
    printf("HELLO\n");
    return 0;
}

int yywrap(void) {
    return 0;
}

int yyerror(char* errormsg) {
    printf("%s\n", errormsg);
    exit(1);
}