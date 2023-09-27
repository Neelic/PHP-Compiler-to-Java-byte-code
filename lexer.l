%option noyywrap
%option never-interactive

%x SINGLE_QUOTE_STRING
%x DOUBLE_QUOTE_STRING
%x MULTILINE_COMMENT

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
NIL		    {printf("Found keyword: %s\n", yytext);}
NAN		    {printf("Found keyword: %s\n", yytext);}
const		{printf("Found keyword: %s\n", yytext);}
global		{printf("Found keyword: %s\n", yytext);}
use		    {printf("Found keyword: %s\n", yytext);}
new		    {printf("Found keyword: %s\n", yytext);}
class		{printf("Found keyword: %s\n", yytext);}
private		{printf("Found keyword: %s\n", yytext);}
public		{printf("Found keyword: %s\n", yytext);}
protected	{printf("Found keyword: %s\n", yytext);}
static		{printf("Found keyword: %s\n", yytext);}
function	{printf("Found keyword: %s\n", yytext);}
for         {printf("Found keyword: %s\n", yytext);}
do			{printf("Found keyword: %s\n", yytext);}
while		{printf("Found keyword: %s\n", yytext);}
switch		{printf("Found keyword: %s\n", yytext);}
case		{printf("Found keyword: %s\n", yytext);}
default		{printf("Found keyword: %s\n", yytext);}
break		{printf("Found keyword: %s\n", yytext);}
if			{printf("Found keyword: %s\n", yytext);}
else		{printf("Found keyword: %s\n", yytext);}
elseif      {printf("Found keyword: %s\n", yytext);}
match		{printf("Found keyword: %s\n", yytext);}
true        {printf("Found keyword: %s\n", yytext);}
false       {printf("Found keyword: %s\n", yytext);}

"|"		    {printf("Found special symbol: %s\n", yytext);}
";"         {printf("Found special symbol: %s\n", yytext);}
"("		    {printf("Found special symbol: %s\n", yytext);}
")"		    {printf("Found special symbol: %s\n", yytext);}
"["		    {printf("Found special symbol: %s\n", yytext);}
"]"		    {printf("Found special symbol: %s\n", yytext);}
"{"		    {printf("Found special symbol: %s\n", yytext);}
"}"		    {printf("Found special symbol: %s\n", yytext);}

"+"         {printf("Found arithmetic operation: %s\n", yytext);}
"++"        {printf("Found arithmetic operation: %s\n", yytext);}    
"-"         {printf("Found arithmetic operation: %s\n", yytext);}
"--"        {printf("Found arithmetic operation: %s\n", yytext);}
"*"         {printf("Found arithmetic operation: %s\n", yytext);}
"**"        {printf("Found arithmetic operation: %s\n", yytext);}
"/"         {printf("Found arithmetic operation: %s\n", yytext);}
"%"         {printf("Found arithmetic operation: %s\n", yytext);}
"="         {printf("Found arithmetic operation: %s\n", yytext);}
"+="        {printf("Found arithmetic operation: %s\n", yytext);}
"-="        {printf("Found arithmetic operation: %s\n", yytext);}
"*="        {printf("Found arithmetic operation: %s\n", yytext);}
"/="        {printf("Found arithmetic operation: %s\n", yytext);}
"%="        {printf("Found arithmetic operation: %s\n", yytext);}
"**="       {printf("Found arithmetic operation: %s\n", yytext);}

"=="        {printf("Found operation: %s\n", yytext);}
"!="        {printf("Found operation: %s\n", yytext);}
">"         {printf("Found operation: %s\n", yytext);}
"<"         {printf("Found operation: %s\n", yytext);}
">="        {printf("Found operation: %s\n", yytext);}
"<="        {printf("Found operation: %s\n", yytext);}
"==="       {printf("Found operation: %s\n", yytext);}
"&&"        {printf("Found operation: %s\n", yytext);}
"||"        {printf("Found operation: %s\n", yytext);}
"!"         {printf("Found operation: %s\n", yytext);}

"->"		{printf("Found operation: %s\n", yytext);}
"=>"		{printf("Found operation: %s\n", yytext);}
"..."       {printf("Found operation: %s\n", yytext);}
"$" 		{printf("Found operation: %s\n", yytext);}
"::"        {printf("Found operation: %s\n", yytext);}
"."		    {printf("Found operation: %s\n", yytext);}

\\n           {lineCount += 1;}
"<?"          {printf("Found start php code section: %s\n", yytext);}
"<?php"       {printf("Found start php code section: %s\n", yytext);}
"?>"          {printf("Found end php code section: %s\n", yytext);}
{IDENTIFIER}  {printf("Found identifier: %s\n", yytext);}
#.*           {printf("Found single-line comment: %s\n", yytext + 1);}
\/\/.*        {printf("Found single-line comment: %s\n", yytext + 2);}
{DIGIT}+      {printf("Found integer number: %s\n", yytext);}

<INITIAL>"/*" {
    BEGIN(MULTILINE_COMMENT);
    printf("Found multiline comment:\n");
}

\' {
    str[0] = '\0';
    BEGIN(SINGLE_QUOTE_STRING);
}

\" {
    str[0] = '\0';
    BEGIN(DOUBLE_QUOTE_STRING);
}

<MULTILINE_COMMENT>.|\n {printf("%s", yytext);}
<MULTILINE_COMMENT>"*/" {BEGIN(INITIAL);}

<SINGLE_QUOTE_STRING>[^\'\\\n]+ {strcat(str, yytext);} 
<SINGLE_QUOTE_STRING>\' { 
    printf("found string literal: %s\n", str);
    BEGIN(INITIAL);
}

<DOUBLE_QUOTE_STRING>[^\"\\\n]+ {strcat(str, yytext);}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\\n {strcat(str, "\n");}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\\\\ {strcat(str, "\\");}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\\\" {strcat(str, "\"");}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\n {yyerror("Line break inside literal", lineCount);}
<DOUBLE_QUOTE_STRING><SINGLE_QUOTE_STRING>\<\<EOF\>\> {yyerror("Unclosed string", lineCount);}
<DOUBLE_QUOTE_STRING>{IDENTIFIER} {
    //TODO Сделать обработку интерполяции строки
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