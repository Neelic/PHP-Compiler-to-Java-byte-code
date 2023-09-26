%option noyywrap
%option never-interactive

%x SINGLE_QUOTE_STRING
%x DOUBLE_QUOTE_STRING

VARIABLE \$^[a-zA-Z_][a-zA-Z0-9_]*
DIGIT [0-9]
EXPONENT [eE][+-]?[1-9]{DIGIT}*(_{DIGIT}+)*
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yyerror(char* errormsg, int lineCount);
    int lineCount = 1;
%}

%%

%{
    char str[1000];
%}

null		{printf("Found keyword: %s\n", yytext);}
break		{printf("Found keyword: %s\n", yytext);}
class		{printf("Found keyword: %s\n", yytext);}
for         {printf("Found keyword: %s\n", yytext);}
do			{printf("Found keyword: %s\n", yytext);}
while		{printf("Found keyword: %s\n", yytext);}
case		{printf("Found keyword: %s\n", yytext);}
if			{printf("Found keyword: %s\n", yytext);}
else		{printf("Found keyword: %s\n", yytext);}
elseif      {printf("Found keyword: %s\n", yytext);}
match		{printf("Found keyword: %s\n", yytext);}
true        {printf("Found keyword: %s\n", yytext);}
false       {printf("Found keyword: %s\n", yytext);}


"+"         {printf("Found arithmetic operation: %s\n", yytext);}   
"-"         {printf("Found arithmetic operation: %s\n", yytext);}
"*"         {printf("Found arithmetic operation: %s\n", yytext);}
"/"         {printf("Found arithmetic operation: %s\n", yytext);}
"%"         {printf("Found arithmetic operation: %s\n", yytext);}

";"         {printf("Found special symbol: %s\n", yytext);}

{VARIABLE} {printf("Found variable literal: %s\n", yytext);}

\' {
    str[0] = "\0";
    BEGIN(SINGLE_QUOTE_STRING);
}

\" {
    str[0] = "\0";
    BEGIN(DOUBLE_QUOTE_STRING);
}

\\n         {lineCount += 1;}

<SINGLE_QUOTE_STRING>[^\'\\\n]+ {strcat(str, yytext);} 
<SINGLE_QUOTE_STRING>\' { 
    printf("found string literal: %s\n", str);
    BEGIN(INITIAL);
}

<SINGLE_QUOTE_STRING>[^\'\\\n]+ {strcat(str, yytext);} 
<SINGLE_QUOTE_STRING>\' { 
    printf("Found string literal: %s\n", str);
    BEGIN(INITIAL);
}

<DOUBLE_QUOTE_STRING>[^\"\\\n]+ {strcat(str, yytext);}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\\n {strcat(str, "\n");}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\\\\ {strcat(str, "\\");}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\\\" {strcat(str, "\"");}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\n {yyerror("Line break inside literal", lineCount);}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\<\<EOF\>\> {yyerror("Unclosed string", lineCount);}
<DOUBLE_QUOTE_STRING>{VARIABLE} {
    strcat(str, " variable! ");
}
<DOUBLE_QUOTE_STRING>\" { 
    printf("Found string literal: %s\n", str);
    BEGIN(INITIAL);
}

%%

int main(void) {
    FILE *file = fopen("example.php", "r");
    if (file == NULL) {
        printf("File opening error");
        return 1;
    }

    yyin = file;

    while (yylex() != 0);

    fclose(file);

    return 0;
}

int yyerror(char* errormsg, int lineCount) {
    printf("ERROR! %s on line %d\n", errormsg, lineCount);
    exit(1);
}