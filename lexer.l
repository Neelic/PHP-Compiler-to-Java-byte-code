%option noyywrap
%option never-interactive
%x STRING 

%{
    #include <stdio.h>
    int yyerror(char* errormsg);
%}

%%

%{
    char str[1000];
%}

[\t\n]+                            // skip white space chars.

\" {
    str[0] = 0;
    BEGIN(STRING);
}

<STRING>[^\"\\\n]+ {strcat(str, yytext);} 
<STRING>\\n {strcat(str, "\n");}
<STRING>\\\\ {strcat(str, "\\");}
<STRING>\\\" {strcat(str, "\"");}
<STRING>\n {yyerror("ERROR! line break inside literal");}
<STRING><<EOF>> {yyerror("ERROR! unclosed ");}
<STRING>\" { 
    printf("found string literal: %s\n", str);
    BEGIN(INITIAL);
}

%%

int main(int argc, char* acrgv) {
    printf("HELLO\n");
    return 0;
}

int yyerror(char* errormsg) {
    printf("%s\n", errormsg);
    exit(1);
}