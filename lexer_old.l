%option noyywrap
%option never-interactive
%{
    #include <stdio.h>
    #include <string.h>
    int yyerror(char* errormsg);
%}

%x SEMICOLON
%x VARIABLE
%x GENERAL_STRING
%x SINGLE_QUOTE_STRING
%x DOUBLE_QUOTE_STRING 

%%

%{
    char str[1000];
%}

if { printf("FOUND SOMETHING ABFUEBUCUEBCUE"); }

\; {
    str[0] = 0;
    BEGIN(SEMICOLON);
}

<SEMICOLON>\* {printf("found semicolon literal: %s\n", yytext); BEGIN(INITIAL);}

\$^[a-zA-Z_\x80-\xff][a-zA-Z0-9_\x80-\xff]*$ {
    str[0] = 0;
    BEGIN(VARIABLE);
}

<VARIABLE>.* {printf("found variable literal: %s\n", yytext);}

<GENERAL_STRING>\\n {strcat(str, "\n");}
<GENERAL_STRING>\\\\ {strcat(str, "\\");}
<GENERAL_STRING>\\\" {strcat(str, "\"");}
<GENERAL_STRING>\n {yyerror("ERROR! line break inside literal");}
<GENERAL_STRING><<EOF>> {yyerror("ERROR! unclosed ");}

\' {
    str[0] = 0;
    BEGIN(SINGLE_QUOTE_STRING,GENERAL_STRING);
}

<SINGLE_QUOTE_STRING,GENERAL_STRING>[^\'\\\n]+ {strcat(str, yytext);} 
<SINGLE_QUOTE_STRING,GENERAL_STRING>\' { 
    printf("found string literal: %s\n", str);
    BEGIN(INITIAL);
}

\" {
    str[0] = 0;
    BEGIN(DOUBLE_QUOTE_STRING,GENERAL_STRING);
}

<DOUBLE_QUOTE_STRING,GENERAL_STRING>[^\"\\\n]+ {strcat(str, yytext);}
<DOUBLE_QUOTE_STRING,GENERAL_STRING>\$^[a-zA-Z_\x80-\xff][a-zA-Z0-9_\x80-\xff]*$ {
    strcat(str, "");
    BEGIN(VARIABLE);
    BEGIN(DOUBLE_QUOTE_STRING,GENERAL_STRING);
}
<DOUBLE_QUOTE_STRING,GENERAL_STRING>\" { 
    printf("found string literal: %s\n", str);
    BEGIN(INITIAL);
}

%%

int main(void) {
    
    yyin = fopen("example.php","r");

    yylex();
    
    fclose(yyin);
    return 0;
}

int yyerror(char* errormsg) {
    printf("%s\n", errormsg);
    exit(1);
}