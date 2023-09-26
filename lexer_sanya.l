%option noyywrap
%option never-interactive

%{
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
%}

DIGIT [0-9]
HEX_DIGIT [0-9A-Fa-f]
BIN_DIGIT [01]
OCT_DIGIT [0-7]
EXPONENT [eE][+-]?[1-9]{DIGIT}*(_{DIGIT}+)*
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

%x DOUBLE_QUOTE_STRING
%x SINGLE_QUOTE_STRING
%x ML_COMMENT

%%

%{
    int num;
    int doubleQuote;
    char temp1[100];
    char string[1000];
    int nestingCount = 0;
%}

alias		{ printf("Found keyword: %s\n", yytext); }
and			{ printf("Found keyword: %s\n", yytext); }
begin		{ printf("Found keyword: %s\n", yytext); }
break		{ printf("Found keyword: %s\n", yytext); }
case		{ printf("Found keyword: %s\n", yytext); }
class		{ printf("Found keyword: %s\n", yytext); }
def			{ printf("Found keyword: %s\n", yytext); }
"defined?"	{ printf("Found keyword: %s\n", yytext); }
do			{ printf("Found keyword: %s\n", yytext); }
if			{ printf("Found keyword: %s\n", yytext); }
else		{ printf("Found keyword: %s\n", yytext); }
elsif		{ printf("Found keyword: %s\n", yytext); }
end			{ printf("Found keyword: %s\n", yytext); }
ensure		{ printf("Found keyword: %s\n", yytext); }
false		{ printf("Found keyword: %s\n", yytext); }
for			{ printf("Found keyword: %s\n", yytext); }
in			{ printf("Found keyword: %s\n", yytext); }
module		{ printf("Found keyword: %s\n", yytext); }
next		{ printf("Found keyword: %s\n", yytext); }
nil			{ printf("Found keyword: %s\n", yytext); }
not			{ printf("Found keyword: %s\n", yytext); }
or			{ printf("Found keyword: %s\n", yytext); }
redo		{ printf("Found keyword: %s\n", yytext); }
rescue		{ printf("Found keyword: %s\n", yytext); }
retry		{ printf("Found keyword: %s\n", yytext); }
return		{ printf("Found keyword: %s\n", yytext); }
self		{ printf("Found keyword: %s\n", yytext); }
super		{ printf("Found keyword: %s\n", yytext); }
then		{ printf("Found keyword: %s\n", yytext); }
true		{ printf("Found keyword: %s\n", yytext); }
undef		{ printf("Found keyword: %s\n", yytext); }
unless		{ printf("Found keyword: %s\n", yytext); }
until		{ printf("Found keyword: %s\n", yytext); }
when		{ printf("Found keyword: %s\n", yytext); }
while		{ printf("Found keyword: %s\n", yytext); }
yield		{ printf("Found keyword: %s\n", yytext); }

"+"         { printf("Found arithmetic operation: %s\n", yytext); }   
"-"         { printf("Found arithmetic operation: %s\n", yytext); }
"*"         { printf("Found arithmetic operation: %s\n", yytext); }
"/"         { printf("Found arithmetic operation: %s\n", yytext); }
"%"         { printf("Found arithmetic operation: %s\n", yytext); }
"**"        { printf("Found arithmetic operation: %s\n", yytext); }

"=="        { printf("Found arithmetic operation: %s\n", yytext); }
"!="        { printf("Found arithmetic operation: %s\n", yytext); }
">"         { printf("Found arithmetic operation: %s\n", yytext); }
"<"         { printf("Found arithmetic operation: %s\n", yytext); }
">="        { printf("Found arithmetic operation: %s\n", yytext); }
"<="        { printf("Found arithmetic operation: %s\n", yytext); }
"<=>"       { printf("Found arithmetic operation: %s\n", yytext); }
"==="       { printf("Found arithmetic operation: %s\n", yytext); }
"eql?"      { printf("Found arithmetic operation: %s\n", yytext); }
"equal?"    { printf("Found arithmetic operation: %s\n", yytext); }

"="         { printf("Found arithmetic operation: %s\n", yytext); }
"+="        { printf("Found arithmetic operation: %s\n", yytext); }
"-="        { printf("Found arithmetic operation: %s\n", yytext); }
"*="        { printf("Found arithmetic operation: %s\n", yytext); }
"/="        { printf("Found arithmetic operation: %s\n", yytext); }
"%="        { printf("Found arithmetic operation: %s\n", yytext); }
"**="       { printf("Found arithmetic operation: %s\n", yytext); }

"&"         { printf("Found operation: %s\n", yytext); }
"|"         { printf("Found operation: %s\n", yytext); }
"^"         { printf("Found operation: %s\n", yytext); }
"~"         { printf("Found operation: %s\n", yytext); }
"<<"        { printf("Found comparison operation: %s\n", yytext); }
">>"        { printf("Found comparison operation: %s\n", yytext); }

"&&"        { printf("Found operation: %s\n", yytext); }
"||"        { printf("Found operation: %s\n", yytext); }
"!"         { printf("Found operation: %s\n", yytext); }

".."        { printf("Found operation: %s\n", yytext); }
"..."       { printf("Found operation: %s\n", yytext); }

"("         { printf("Found bracket: %s\n", yytext); }
")"         { printf("Found bracket: %s\n", yytext); }
"{"         { printf("Found bracket: %s\n", yytext); }
"}"         {
                if(nestingCount == 0) {
                    printf("Found bracket: %s\n", yytext);
                } else {
                    nestingCount--;
                    BEGIN(STRING);
                    string[0] = 0;
                    printf("Found interpolation: +\n");
                }
            }
"["         { printf("Found bracket: %s\n", yytext); }
"]"         { printf("Found bracket: %s\n", yytext); }
"@"         { printf("Found doge: %s\n", yytext); }

"?"         { printf("Found question symbol: %s\n", yytext); }

"."         { printf("Found special symbol: %s\n", yytext); }
","         { printf("Found special symbol: %s\n", yytext); }
":"         { printf("Found special symbol: %s\n", yytext); }
"::"        { printf("Found special symbol: %s\n", yytext); }
";"         { printf("Found special symbol: %s\n", yytext); }

\"          {
                string[0] = '\0'; 
                BEGIN(DOUBLE_QUOTE_STRING);
            }
                
\'          {
                string[0] = '\0'; 
                BEGIN(SINGLE_QUOTE_STRING);    
            }

{IDENTIFIER}    { printf("Found identifier: %s\n", yytext); }

[a-z_][a-zA-Z0-9_]* {printf("Found method name: %s\n", yytext); }
[A-Z][a-zA-Z0-9_]* {printf("Found class name: %s\n", yytext); }
\@[a-z_][a-zA-Z0-9_]* {printf("Found var name: %s\n", yytext); }
\@\@[a-z_][a-zA-Z0-9_]* {printf("Found class var name: %s\n", yytext); }
[A-Z][a-zA-Z0-9_]* {printf("Found constant: %s\n", yytext); }

<DOUBLE_QUOTE_STRING>"#{"   { 
                                printf("Found string \"%s\"\n", string);
                                printf("Found interpolation: +\n");
                                nestingCount++;
                                BEGIN(INITIAL);
                            }

<SINGLE_QUOTE_STRING>[^\\\']+ { strcat(string, yytext); }
<DOUBLE_QUOTE_STRING>[^\\\"\'\n#{}]+ { strcat(string, yytext); }
<DOUBLE_QUOTE_STRING>[#{}]           { strcat(string, yytext); }
<DOUBLE_QUOTE_STRING>\\n             { strcat(string, "\n"); }
<DOUBLE_QUOTE_STRING>\\a             { strcat(string, "\a"); }
<DOUBLE_QUOTE_STRING>\\b             { strcat(string, "\b"); }
<DOUBLE_QUOTE_STRING>\\t             { strcat(string, "\t"); }
<DOUBLE_QUOTE_STRING>\\v             { strcat(string, "\v"); }
<DOUBLE_QUOTE_STRING>\\f             { strcat(string, "\f"); }
<DOUBLE_QUOTE_STRING>\\r             { strcat(string, "\r"); }
<DOUBLE_QUOTE_STRING>\\e             { strcat(string, "\e"); }
<DOUBLE_QUOTE_STRING>\\s             { strcat(string, " "); }
<SINGLE_QUOTE_STRING><DOUBLE_QUOTE_STRING>\\\\            { strcat(string, "\\"); }
<DOUBLE_QUOTE_STRING>\\\"        { strcat(string, "\""); }

<SINGLE_QUOTE_STRING>\\\'        { strcat(string, "'"); }
<DOUBLE_QUOTE_STRING>\\{OCT_DIGIT}{1,3}  { 
                                sscanf(yytext + 1, "%o", &num);
                                temp1[0] = (char) num;
                                temp1[1] = 0;
                                strcat(string, temp1);
                            }

<DOUBLE_QUOTE_STRING>\\x{HEX_DIGIT}{1,2} { 
                                sscanf(yytext + 2, "%x", &num);
                                temp1[0] = (char) num;
                                temp1[1] = 0;
                                strcat(string, temp1);
                            }

<DOUBLE_QUOTE_STRING>\" { 
                                printf("String literal: \"%s\" \n", string);
                                BEGIN(INITIAL);
                        }

<SINGLE_QUOTE_STRING>\' { 
                            printf("String literal: \"%s\" \n", string);
                            BEGIN(INITIAL);
                        }


#.* { printf("Found single-line comment: %s\n", yytext + 1); }



<INITIAL>"=begin" {
    BEGIN(ML_COMMENT);
    printf("Found multiline comment:\n");
}

<ML_COMMENT>"=end" {
    BEGIN(INITIAL);
}

<ML_COMMENT>.|\n {
    printf("%s", yytext);
}



{DIGIT}+       { printf("Found integer: %s\n", yytext); }
0[xX]{HEX_DIGIT}+    { printf("Found hexadecimal integer: %s\n", yytext); }
0[bB]{BIN_DIGIT}+    { printf("Found binary integer: %s\n", yytext); }
{DIGIT}+"."{DIGIT}*   { printf("Found floating-point number: %s\n", yytext); }
{DIGIT}+"."{DIGIT}*{EXPONENT}?  { printf("Found floating-point number: %s\n", yytext); }
{DIGIT}+{EXPONENT}  { printf("Found floating-point number with exponent: %s\n", yytext); }


%%

int main(int argc, char** argv) {
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