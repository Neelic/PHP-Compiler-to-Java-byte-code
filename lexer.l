%option noyywrap
%option never-interactive

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include <iomanip>
    #include <sstream>

    extern int yyparse(void);
    void error_print(char* errormsg, int lineCount, bool isWarning);
    void squeeze (char s[], int c);
%}

%x SINGLE_QUOTE_STRING
%x DOUBLE_QUOTE_STRING
%x SINGLE_LINE_COMMENT
%x MULTILINE_COMMENT
%x NOT_IN_PHP_CODE
%x EXECUTION_OPERATOR

NUMBER [0-9]
INTEGER [1-9][0-9]*(_[0-9]+)*|0
INT_HEXIDECIMAL 0[xX][0-9a-fA-F]+(_[0-9a-fA-F]+)*
INT_OCTAL 0[oO]?[0-7]+(_[0-7]+)*
INT_BINARY 0[bB][01]+(_[01]+)*
FLOAT ({NUMBER}*(_{NUMBER}+)*[\.]{NUMBER}+)|({INTEGER}[\.]{NUMBER}*(_{NUMBER}+)*)
EXPONENT_FLOAT (({INTEGER}|{FLOAT})[eE][+-]{NUMBER}+)
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

SPACE [\t\r\t\f\v ]

%%

%{
    std::string str = "";
    int tmp;
    float test = .0;
    int nestingCount = 0;
    int static lineCount = 1;
    bool static inCode = false;
    BEGIN(NOT_IN_PHP_CODE);
%}

const		        {printf("Found keyword: %s\n", yytext);}
global		        {printf("Found keyword: %s\n", yytext);}
use		            {printf("Found keyword: %s\n", yytext);}
as	    	        {printf("Found keyword: %s\n", yytext);}
callable	        {printf("Found keyword: %s\n", yytext);}
try 		        {printf("Found keyword: %s\n", yytext);}
catch		        {printf("Found keyword: %s\n", yytext);}
clone		        {printf("Found keyword: %s\n", yytext);}
continue	        {printf("Found keyword: %s\n", yytext);}
echo		        {printf("Found keyword: %s\n", yytext);}
enddeclare   	    {printf("Found keyword: %s\n", yytext);}
die	    	        {printf("Found keyword: %s\n", yytext);}
new		            {printf("Found keyword: %s\n", yytext);}
class		        {printf("Found keyword: %s\n", yytext);}
abstract	        {printf("Found keyword: %s\n", yytext);}
private		        {printf("Found keyword: %s\n", yytext);}
public		        {printf("Found keyword: %s\n", yytext);}
protected	        {printf("Found keyword: %s\n", yytext);}
static		        {printf("Found keyword: %s\n", yytext);}
extends         	{printf("Found keyword: %s\n", yytext);}
final         	    {printf("Found keyword: %s\n", yytext);}
finally         	{printf("Found keyword: %s\n", yytext);}
fn          	    {printf("Found keyword: %s\n", yytext);}
implements         	{printf("Found keyword: %s\n", yytext);}
instanceof         	{printf("Found keyword: %s\n", yytext);}
insteadof         	{printf("Found keyword: %s\n", yytext);}
interface         	{printf("Found keyword: %s\n", yytext);}
namespace         	{printf("Found keyword: %s\n", yytext);}
or              	{printf("Found keyword: %s\n", yytext);}
print         	    {printf("Found keyword: %s\n", yytext);}
readonly         	{printf("Found keyword: %s\n", yytext);}
return           	{printf("Found keyword: %s\n", yytext);}
throw           	{printf("Found keyword: %s\n", yytext);}
trait         	    {printf("Found keyword: %s\n", yytext);}
var              	{printf("Found keyword: %s\n", yytext);}
xor              	{printf("Found keyword: %s\n", yytext);}
from                {printf("Found keyword: %s\n", yytext);}
yield            	{printf("Found keyword: %s\n", yytext);}
function	        {printf("Found keyword: %s\n", yytext);}
for                 {printf("Found keyword: %s\n", yytext);}
foreach             {printf("Found keyword: %s\n", yytext);}
endfor         	    {printf("Found keyword: %s\n", yytext);}
endforeach        	{printf("Found keyword: %s\n", yytext);}
do			        {printf("Found keyword: %s\n", yytext);}
while		        {printf("Found keyword: %s\n", yytext);}
endwhile            {printf("Found keyword: %s\n", yytext);}
switch		        {printf("Found keyword: %s\n", yytext);}
endswitch           {printf("Found keyword: %s\n", yytext);}
case		        {printf("Found keyword: %s\n", yytext);}
default		        {printf("Found keyword: %s\n", yytext);}
break		        {printf("Found keyword: %s\n", yytext);}
if			        {printf("Found keyword: %s\n", yytext);}
else		        {printf("Found keyword: %s\n", yytext);}
elseif              {printf("Found keyword: %s\n", yytext);}
endif               {printf("Found keyword: %s\n", yytext);}
match		        {printf("Found keyword: %s\n", yytext);}
and 		        {printf("Found keyword: %s\n", yytext);}
declare             {printf("Found keyword: %s\n", yytext);}
require             {printf("Found keyword: %s\n", yytext);}
include             {printf("Found keyword: %s\n", yytext);}
require_once        {printf("Found keyword: %s\n", yytext);}
include_once        {printf("Found keyword: %s\n", yytext);}
goto                {printf("Found keyword: %s\n", yytext);}

\({SPACE}*[iI][nN][tT]{SPACE}*\)                  {printf("Found int cast: %s\n", yytext);}
\({SPACE}*[iI][nN][tT][eE][gG][eE][rR]{SPACE}*\)  {printf("Found int cast: %s\n", yytext);}
\({SPACE}*[bB][oO][oO][lL]{SPACE}*\)              {printf("Found bool cast: %s\n", yytext);}
\({SPACE}*[bB][oO][oO][lL][eE][aA][nN]{SPACE}*\)  {printf("Found bool cast: %s\n", yytext);}
\({SPACE}*[fF][lL][oO][aA][tT]{SPACE}*\)          {printf("Found float cast: %s\n", yytext);}
\({SPACE}*[dD][oO][uU][bB][lL]{SPACE}*\)          {printf("Found float cast: %s\n", yytext);}
\({SPACE}*[rR][eE][aA][lL]{SPACE}*\)              {printf("Found float cast: %s\n", yytext);}
\({SPACE}*[sS][tT][rR][iI][nN][gG]{SPACE}*\)      {printf("Found string cast: %s\n", yytext);}
\({SPACE}*[bB][iI][nN][aA][rR][yY]{SPACE}*\)      {printf("Found string cast: %s\n", yytext);}
\({SPACE}*[aA][rR][rR][aA][yY]{SPACE}*\)          {printf("Found array cast: %s\n", yytext);}
\({SPACE}*[oO][bB][jJ][eE][cC][tT]{SPACE}*\)      {printf("Found object cast: %s\n", yytext);}

","		            {printf("Found special character: %s\n", yytext);}
";"                 {printf("Found special character: %s\n", yytext);}
"("		            {printf("Found special character: %s\n", yytext);}
")"		            {printf("Found special character: %s\n", yytext);}
"["		            {printf("Found special character: %s\n", yytext);}
"]"		            {printf("Found special character: %s\n", yytext);}
"{"		            {printf("Found special character: %s\n", yytext);}
"}"		            {
                        if(nestingCount == 0) {
                            printf("Found bracket: %s\n", yytext);
                        } else {
                            nestingCount--;
                            BEGIN(DOUBLE_QUOTE_STRING);
                            str = "";
                            printf("Found concatenation: .\n");
                        }
                    }

"+"                 {printf("Found arithmetic operator: %s\n", yytext);}
"++"                {printf("Found arithmetic operator: %s\n", yytext);}    
"-"                 {printf("Found arithmetic operator: %s\n", yytext);}
"--"                {printf("Found arithmetic operator: %s\n", yytext);}
"*"                 {printf("Found arithmetic operator: %s\n", yytext);}
"**"                {printf("Found arithmetic operator: %s\n", yytext);}
"/"                 {printf("Found arithmetic operator: %s\n", yytext);}
"%"                 {printf("Found arithmetic operator: %s\n", yytext);}
"="                 {printf("Found arithmetic operator: %s\n", yytext);}

"&"                 {printf("Found operator: %s\n", yytext);}

"|"                 {printf("Found bitwise operator: %s\n", yytext);}
"^"                 {printf("Found bitwise operator: %s\n", yytext);}
"~"                 {printf("Found bitwise operator: %s\n", yytext);}

"!"                 {printf("Found operator: %s\n", yytext);}
"=="                {printf("Found operator: %s\n", yytext);}
"!="                {printf("Found operator: %s\n", yytext);}
">"                 {printf("Found operator: %s\n", yytext);}
"<"                 {printf("Found operator: %s\n", yytext);}
">="                {printf("Found operator: %s\n", yytext);}
"<="                {printf("Found operator: %s\n", yytext);}
"==="               {printf("Found operator: %s\n", yytext);}
"!=="               {printf("Found operator: %s\n", yytext);}
"&&"                {printf("Found operator: %s\n", yytext);}
"||"                {printf("Found operator: %s\n", yytext);}

">>"                {printf("Found bitwise operator: %s\n", yytext);}
"<<"                {printf("Found bitwise operator: %s\n", yytext);}

"->"		        {printf("Found operator: %s\n", yytext);}
"=>"		        {printf("Found operator: %s\n", yytext);}
"..."               {printf("Found operator: %s\n", yytext);}
"$" 		        {printf("Found operator: %s\n", yytext);}
":"                 {printf("Found operator: %s\n", yytext);}
"::"                {printf("Found operator: %s\n", yytext);}
"."		            {printf("Found operator: %s\n", yytext);}
"@"                 {printf("Found operator: %s\n", yytext);}

\n+                 {lineCount += yyleng;}
{SPACE}+            {}
"?>"                {
                        printf("Found special character: ;\n"); 
                        printf("Found end php code section: %s\n", yytext); 
                        inCode = false; str = ""; 
                        BEGIN(NOT_IN_PHP_CODE);}
{IDENTIFIER}        {printf("Found identifier: %s\n", yytext);}
{INTEGER}           {squeeze(yytext, '_'); printf("Found integer number: %s\n", yytext);}
{INT_HEXIDECIMAL}   {squeeze(yytext, '_'); printf("Found integer hexidecimal number: %s\n", yytext);}
{INT_OCTAL}         {squeeze(yytext, '_'); printf("Found integer octal number: %s\n", yytext);}
{INT_BINARY}        {squeeze(yytext, '_'); printf("Found integer binary number: %s\n", yytext);}
{FLOAT}             {squeeze(yytext, '_'); printf("Found float number: %s\n", yytext);}
{EXPONENT_FLOAT}    {squeeze(yytext, '_'); printf("Found exponent number: %s\n", yytext);}

#|\/\/  {str = ""; BEGIN(SINGLE_LINE_COMMENT);}
"/*"    {str = ""; BEGIN(MULTILINE_COMMENT);}

\'      {str = ""; BEGIN(SINGLE_QUOTE_STRING);}
\"      {str = ""; BEGIN(DOUBLE_QUOTE_STRING);}

"`"     {str = ""; BEGIN(EXECUTION_OPERATOR);}

.       {printf("Unknown character: %s\n", yytext);}

<NOT_IN_PHP_CODE>"<?"     {
                            inCode = true; 
                            BEGIN(INITIAL); 
                            printf("Found html code section: %s\n", str.c_str()); 
                            printf("Found start php code section: %s\n", yytext);
                          }
<NOT_IN_PHP_CODE>"<?php"  {
                            inCode = true; 
                            BEGIN(INITIAL); 
                            printf("Found html code section: %s\n", str.c_str());
                            printf("Found start php code section: %s\n", yytext);
                          }
<NOT_IN_PHP_CODE>[^<\n]+  {str += yytext;}
<NOT_IN_PHP_CODE>\n       {str += yytext; lineCount += yyleng;}
<NOT_IN_PHP_CODE>\<+[^?]  {str += yytext;}
<NOT_IN_PHP_CODE><<EOF>>  {printf("Found html code section: %s\n", str.c_str()); BEGIN(INITIAL);}

<SINGLE_LINE_COMMENT>[^?\n]+  {str += yytext;}
<SINGLE_LINE_COMMENT>\?[^>]   {str += yytext;}
<SINGLE_LINE_COMMENT>"?>" {
                            inCode = false; 
                            printf("Found single-line comment: %s\n", str.c_str());
                            printf("Found end php code section: %s\n", yytext); 
                            str[0] = 0; 
                            BEGIN(NOT_IN_PHP_CODE);
                          }
<SINGLE_LINE_COMMENT>\n   {lineCount += yyleng; printf("Found single-line comment: %s\n", str.c_str()); BEGIN(INITIAL);}

<MULTILINE_COMMENT>[^*\n]+ {str += yytext;}
<MULTILINE_COMMENT>\n      {str += yytext; lineCount += yyleng;}
<MULTILINE_COMMENT>\*[^/]  {str += yytext;}
<MULTILINE_COMMENT>"*/"    {printf("Found multiline comment: %s\n", str.c_str()); BEGIN(INITIAL);}

<EXECUTION_OPERATOR>[^`]+ {str += yytext;}
<EXECUTION_OPERATOR>"`"   {printf("Found shell command: %s\n", str.c_str()); BEGIN(INITIAL);}

<SINGLE_QUOTE_STRING>[^\'\\]+   {str += yytext;}
<SINGLE_QUOTE_STRING>\\\'       {str += "\'";}
<SINGLE_QUOTE_STRING>\\         {str += "\\";}
<SINGLE_QUOTE_STRING>\'         {printf("Found string literal: %s\n", str.c_str()); BEGIN(INITIAL);}


<DOUBLE_QUOTE_STRING>[^\"\\\n\{$]+           {str += yytext;}
<DOUBLE_QUOTE_STRING>\n                      {str += yytext; lineCount += yyleng;}
<DOUBLE_QUOTE_STRING>\\n                     {str += "\n";}
<DOUBLE_QUOTE_STRING>\\r                     {str += "\r";}
<DOUBLE_QUOTE_STRING>\\t                     {str += "\t";}
<DOUBLE_QUOTE_STRING>\\v                     {str += "\v";}
<DOUBLE_QUOTE_STRING>\\e                     {str += "\e";}
<DOUBLE_QUOTE_STRING>\\f                     {str += "\f";}
<DOUBLE_QUOTE_STRING>\\\"                    {str += "\"";}
<DOUBLE_QUOTE_STRING>\\\$                    {str += "$";}
<DOUBLE_QUOTE_STRING>\\[^nrtvefu"$\\]       {str += yytext;}
<DOUBLE_QUOTE_STRING>\\x[0-9A-Fa-f]{1,2}     {std::stringstream stream;
                                              stream << std::__cxx11::stoi(yytext + 2);
                                              stream >> std::hex >> tmp;
                                              str += (char) tmp;}
<DOUBLE_QUOTE_STRING>\\u\{[0-9A-Fa-f]+\}     {std::string temp = ""; 
                                              temp += yytext+3; 
                                              temp.erase(temp.find('}'), 1);
                                              std::stringstream stream;
                                              stream << std::__cxx11::stoi(temp);
                                              stream >> std::hex >> tmp;
                                              str += (char) tmp;}
<DOUBLE_QUOTE_STRING>\\u\{[^0-9A-Fa-f]\}      {str += yytext;}
<DOUBLE_QUOTE_STRING>\\u[^{]*                {str += yytext;}
<DOUBLE_QUOTE_STRING>\\u\{[^}]*              {str += yytext;}
<DOUBLE_QUOTE_STRING,SINGLE_QUOTE_STRING>\\\\          {str += "\\";}
<DOUBLE_QUOTE_STRING,SINGLE_QUOTE_STRING><<EOF>>     {error_print("Unclosed string", lineCount, false);}
<DOUBLE_QUOTE_STRING>\{[^$]                          {str += yytext;}
<DOUBLE_QUOTE_STRING>\{\$ {
    printf("Found string %s\n", str.c_str());
    printf("Found concatenation: .\n");
    printf("Found operation: $\n");
    nestingCount++;
    BEGIN(INITIAL);
}
<DOUBLE_QUOTE_STRING>\$[^a-zA-Z_]?   {str += yytext;}
<DOUBLE_QUOTE_STRING>\${IDENTIFIER} {
    error_print("Non supported interpolation", lineCount, true);
    str += yytext;
}
<DOUBLE_QUOTE_STRING>\" { 
    if (nestingCount > 0){
        error_print("Unclosed interpolation", lineCount, false);
    }
    printf("Found string literal: %s\n", str.c_str());
    BEGIN(INITIAL);
}

%%

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if (argc > 1) {
        file = fopen(argv[1], "r");
    }

    if (file == NULL) {
        printf("File opening error");
        return 1;
    }

    yyin = file;

    while (yylex() != 0);
    /* yyparse(); */

    fclose(file);

    return 0;
}

void error_print(char* errormsg, int lineCount, bool isWarning) {
    if (!isWarning) {
        printf("ERROR: %s on line %d\n", errormsg, lineCount);
        exit(0);
    } else {
        printf("WARNING: %s on line %d\n", errormsg, lineCount);
    }
}

void squeeze (char s[], int c) {
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    
    s[j] = 0;
}