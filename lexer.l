%option noyywrap
%option never-interactive

%x GENERAL_STRING
%x SINGLE_QUOTE_STRING
%x DOUBLE_QUOTE_STRING

DIGIT [0-9]
EXPONENT [eE][+-]?[1-9]{DIGIT}*(_{DIGIT}+)*
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yyerror(char* errormsg);
    int lineCount = 0;
%}

%%

%{
    char str[1000];
%}

";" {printf("found semicolon literal: %s\n", yytext);}

\$^[a-zA-Z_][a-zA-Z0-9_]* {printf("found variable literal: %s\n", yytext);}

<GENERAL_STRING>\\n {strcat(str, "\n");}
<GENERAL_STRING>\\\\ {strcat(str, "\\");}
<GENERAL_STRING>\\\" {strcat(str, "\"");}
<GENERAL_STRING>\n {yyerror("ERROR! line break inside literal");}
<GENERAL_STRING><<EOF>> {yyerror("ERROR! unclosed ");}

\' {
    str[0] = 0;
    BEGIN(SINGLE_QUOTE_STRING);
}

<SINGLE_QUOTE_STRING>[^\'\\\n]+ {strcat(str, yytext);} 
<SINGLE_QUOTE_STRING>\' { 
    printf("found string literal: %s\n", str);
    BEGIN(INITIAL);
}

\" {
    str[0] = "\0";
    BEGIN(DOUBLE_QUOTE_STRING);
}

<DOUBLE_QUOTE_STRING>[^\"\\\n]+ {strcat(str, yytext);}
<DOUBLE_QUOTE_STRING>\\n {strcat(str, "\n");}
<DOUBLE_QUOTE_STRING>\\\\ {strcat(str, "\\");}
<DOUBLE_QUOTE_STRING>\\\" {strcat(str, "\"");}
<DOUBLE_QUOTE_STRING>\n {yyerror("Line break inside literal");}
<DOUBLE_QUOTE_STRING><<EOF>> {yyerror("Unclosed string");}
<DOUBLE_QUOTE_STRING>\$^[a-zA-Z_][a-zA-Z0-9_]*$ {
    strcat(str, "");
    BEGIN(VARIABLE);
    BEGIN(DOUBLE_QUOTE_STRING);
}
<DOUBLE_QUOTE_STRING>\" { 
    printf("found string literal: %s\n", str);
    BEGIN(INITIAL);
}

%%

int main(int argc, char* acrgv) {
    if (argc != 2) {
        printf("You need to specify file name");
        return 1;
    }

    const char *filename = argv[1];
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening error");
        return 1;
    }

    yyin = file;

    while (yylex() != 0);

    fclose(file);

    return 0;
}

int yyerror(char* errormsg) {
    printf("ERROR! %s\n", errormsg);
    exit(1);
}