%option noyywrap
%option never-interactive

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <iostream>
  #include <iomanip>
  #include <sstream>
  #include <vector>
  // #include "FlexLexer.h"
  #include "parser.tab.h"

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
  static std::vector<int> mis_symbols;
  int tmp;
  float test = .0;
  int nestingCount = 0;
  static int lineCount = 1;
  static bool inCode = false;

  if (!mis_symbols.empty()) {
    int tmp = mis_symbols[mis_symbols.size() - 1];
    mis_symbols.pop_back();
    return tmp;
  }

  if (!inCode)
    BEGIN(NOT_IN_PHP_CODE);
%}

const		          {printf("Found keyword: %s\n", yytext); return CONST;}
global		        {printf("Found keyword: %s\n", yytext); return GLOBAL;}
use		            {printf("Found keyword: %s\n", yytext); return USE;}
as	    	        {printf("Found keyword: %s\n", yytext); return AS;}
try 		          {printf("Found keyword: %s\n", yytext); return TRY;}
catch		          {printf("Found keyword: %s\n", yytext); return CATCH;}
clone		          {printf("Found keyword: %s\n", yytext); return CLONE;}
continue	        {printf("Found keyword: %s\n", yytext); return CONTINUE;}
echo		          {printf("Found keyword: %s\n", yytext); return T_ECHO;}
die	    	        {printf("Found keyword: %s\n", yytext); /*return DIE;*/}
new		            {printf("Found keyword: %s\n", yytext); return NEW;}
class		          {printf("Found keyword: %s\n", yytext); return CLASS;}
abstract	        {printf("Found keyword: %s\n", yytext); return ABSTRACT;}
private		        {printf("Found keyword: %s\n", yytext); return PRIVATE;}
public		        {printf("Found keyword: %s\n", yytext); return PUBLIC;}
protected	        {printf("Found keyword: %s\n", yytext); return PROTECTED;}
static		        {printf("Found keyword: %s\n", yytext); return STATIC;}
extends         	{printf("Found keyword: %s\n", yytext); return EXTENDS;}
final         	  {printf("Found keyword: %s\n", yytext); return FINAL;}
finally         	{printf("Found keyword: %s\n", yytext); return FINALLY;}
fn          	    {printf("Found keyword: %s\n", yytext); return FN;}
implements        {printf("Found keyword: %s\n", yytext); return IMPLEMENTS;}
instanceof        {printf("Found keyword: %s\n", yytext); /* return INSTANCE_OF; */}
interface         {printf("Found keyword: %s\n", yytext); return INTERFACE;}
namespace         {printf("Found keyword: %s\n", yytext); /* return NAMESPACE; */}
or              	{printf("Found keyword: %s\n", yytext); return LOGIC_OR;}
print         	  {printf("Found keyword: %s\n", yytext); return T_ECHO;}
readonly         	{printf("Found keyword: %s\n", yytext); return READ_ONLY;}
return           	{printf("Found keyword: %s\n", yytext); return RETURN;}
throw           	{printf("Found keyword: %s\n", yytext); return THROW;}
trait         	  {printf("Found keyword: %s\n", yytext); return TRAIT;}
var              	{printf("Found keyword: %s\n", yytext); /* return VAR; */}
xor              	{printf("Found keyword: %s\n", yytext); return LOGIC_XOR;}
from              {printf("Found keyword: %s\n", yytext); /* return FROM; */}
function	        {printf("Found keyword: %s\n", yytext); return FUNCTION;}
for               {printf("Found keyword: %s\n", yytext); return FOR;}
foreach           {printf("Found keyword: %s\n", yytext); return FOREACH;}
endfor         	  {printf("Found keyword: %s\n", yytext); return END_FOR;}
endforeach        {printf("Found keyword: %s\n", yytext); return END_FOREACH;}
do			          {printf("Found keyword: %s\n", yytext); return DO;}
while		          {printf("Found keyword: %s\n", yytext); return WHILE;}
endwhile          {printf("Found keyword: %s\n", yytext); return END_WHILE;}
switch		        {printf("Found keyword: %s\n", yytext); return SWITCH;}
endswitch         {printf("Found keyword: %s\n", yytext); return END_SWITCH;}
case		          {printf("Found keyword: %s\n", yytext); return CASE;}
default		        {printf("Found keyword: %s\n", yytext); return DEFAULT;}
break		          {printf("Found keyword: %s\n", yytext); return BREAK;}
if			          {printf("Found keyword: %s\n", yytext); return IF;}
else		          {printf("Found keyword: %s\n", yytext); return ELSE;}
elseif            {printf("Found keyword: %s\n", yytext); mis_symbols.push_back(IF); return ELSE; /*! TODO Не факт, что работает*/}
endif             {printf("Found keyword: %s\n", yytext); return END_IF;}
match		          {printf("Found keyword: %s\n", yytext); return MATCH;}
and 		          {printf("Found keyword: %s\n", yytext); return LOGIC_AND;}
declare           {printf("Found keyword: %s\n", yytext); /*return DECLARE;*/}
require           {printf("Found keyword: %s\n", yytext); /*return REQUIRE;*/}
include           {printf("Found keyword: %s\n", yytext); /*return INCLUDE;*/}
require_once      {printf("Found keyword: %s\n", yytext); /*return REQUIRE_ONCE;*/}
include_once      {printf("Found keyword: %s\n", yytext); /*return INCLUDE_ONCE;*/}
goto              {printf("Found keyword: %s\n", yytext); /*return GO_TO;*/}
this              {printf("Found keyword: %s\n", yytext); return THIS;}
self              {printf("Found keyword: %s\n", yytext); return SELF;}

\({SPACE}*[iI][nN][tT]{SPACE}*\)                  {printf("Found int cast: %s\n", yytext); return INT_CAST;}
\({SPACE}*[iI][nN][tT][eE][gG][eE][rR]{SPACE}*\)  {printf("Found int cast: %s\n", yytext); return INT_CAST;}
\({SPACE}*[bB][oO][oO][lL]{SPACE}*\)              {printf("Found bool cast: %s\n", yytext); return BOOL_CAST;}
\({SPACE}*[bB][oO][oO][lL][eE][aA][nN]{SPACE}*\)  {printf("Found bool cast: %s\n", yytext); return BOOL_CAST;}
\({SPACE}*[fF][lL][oO][aA][tT]{SPACE}*\)          {printf("Found float cast: %s\n", yytext); return FLOAT_CAST;}
\({SPACE}*[dD][oO][uU][bB][lL]{SPACE}*\)          {printf("Found float cast: %s\n", yytext); return FLOAT_CAST;}
\({SPACE}*[rR][eE][aA][lL]{SPACE}*\)              {printf("Found float cast: %s\n", yytext); return FLOAT_CAST;}
\({SPACE}*[sS][tT][rR][iI][nN][gG]{SPACE}*\)      {printf("Found string cast: %s\n", yytext); return STRING_CAST;}
\({SPACE}*[bB][iI][nN][aA][rR][yY]{SPACE}*\)      {printf("Found string cast: %s\n", yytext); return STRING_CAST;}
\({SPACE}*[aA][rR][rR][aA][yY]{SPACE}*\)          {printf("Found array cast: %s\n", yytext); return ARRAY_CAST;}
\({SPACE}*[oO][bB][jJ][eE][cC][tT]{SPACE}*\)      {printf("Found object cast: %s\n", yytext); return OBJECT_CAST;}

","		            {printf("Found special character: %s\n", yytext); return ',';}
";"               {printf("Found special character: %s\n", yytext); return ';';}
"("		            {printf("Found special character: %s\n", yytext); return '(';}
")"		            {printf("Found special character: %s\n", yytext); return ')';}
"["		            {printf("Found special character: %s\n", yytext); return '[';}
"]"		            {printf("Found special character: %s\n", yytext); return ']';}
"{"		            {printf("Found special character: %s\n", yytext); return '{';}
"}"		            {
                        if(nestingCount == 0) {
                            printf("Found bracket: %s\n", yytext);
                            return '}';
                        } else {
                            nestingCount--;
                            BEGIN(DOUBLE_QUOTE_STRING);
                            str = "";
                            printf("Found concatenation: .\n");
                        }
                    }

"+"                 {printf("Found arithmetic operator: %s\n", yytext); return '+';}
"++"                {printf("Found arithmetic operator: %s\n", yytext); return INC;}    
"-"                 {printf("Found arithmetic operator: %s\n", yytext); return '-';}
"--"                {printf("Found arithmetic operator: %s\n", yytext); return DEC;}
"*"                 {printf("Found arithmetic operator: %s\n", yytext); return '*';}
"**"                {printf("Found arithmetic operator: %s\n", yytext); return POW;}
"/"                 {printf("Found arithmetic operator: %s\n", yytext); return '/';}
"%"                 {printf("Found arithmetic operator: %s\n", yytext); return '%';}
"="                 {printf("Found arithmetic operator: %s\n", yytext); return '=';}

"&"                 {printf("Found operator: %s\n", yytext); return '&';}

"|"                 {printf("Found bitwise operator: %s\n", yytext); return '|';}
"^"                 {printf("Found bitwise operator: %s\n", yytext); return '^';}
"~"                 {printf("Found bitwise operator: %s\n", yytext); return '~';}

"!"                 {printf("Found operator: %s\n", yytext); return '!';}
"=="                {printf("Found operator: %s\n", yytext); return EQUAL;}
"!="                {printf("Found operator: %s\n", yytext); return EQU_NOT;}
">"                 {printf("Found operator: %s\n", yytext); return '>';}
"<"                 {printf("Found operator: %s\n", yytext); return '<';}
">="                {printf("Found operator: %s\n", yytext); return EQU_MORE;}
"<="                {printf("Found operator: %s\n", yytext); return EQU_LESS;}
"==="               {printf("Found operator: %s\n", yytext); return EQUAL_STRICT;}
"!=="               {printf("Found operator: %s\n", yytext); /*return EQU_NOT_STRICT;*/}
"&&"                {printf("Found operator: %s\n", yytext); return BOOLEAN_AND;}
"||"                {printf("Found operator: %s\n", yytext); return BOOLEAN_OR;}

">>"                {printf("Found bitwise operator: %s\n", yytext); return SHIFT_R;}
"<<"                {printf("Found bitwise operator: %s\n", yytext); return SHIFT_L;}

"->"		            {printf("Found operator: %s\n", yytext); return R_ARROW;}
"=>"		            {printf("Found operator: %s\n", yytext); return R_DOUBLE_ARROW;}
"..."               {printf("Found operator: %s\n", yytext); /*return DECOMPOS_OP;*/}
"$" 		            {printf("Found operator: %s\n", yytext); return '$';}
":"                 {printf("Found operator: %s\n", yytext); return ':';}
"::"                {printf("Found operator: %s\n", yytext); return QUARTER_DOT;}
"."		              {printf("Found operator: %s\n", yytext); return '.';}
"@"                 {printf("Found operator: %s\n", yytext); return '@';}

\n+                 {lineCount += yyleng;}
{SPACE}+            {}
"?>"                {
                      printf("Found special character: ;\n"); 
                      printf("Found end php code section: %s\n", yytext); 
                      inCode = false; 
                      str = ""; 
                      mis_symbols.push_back(END_CODE_PHP_TAG); /*! TODO Не факт, что работает */
                      BEGIN(NOT_IN_PHP_CODE);
                      return ';';
                    }
{IDENTIFIER}        { printf("Found identifier: %s\n", yytext);
                      std::string tmp = std::string(yytext);
                      yylval.sval=&tmp;
                      return ID;}
{INTEGER}           {squeeze(yytext, '_'); printf("Found integer number: %s\n", yytext); yylval.ival=atoi(yytext); return INT_NUMBER;}
{INT_HEXIDECIMAL}   {squeeze(yytext, '_'); printf("Found integer hexidecimal number: %s\n", yytext); /*TODO do convert*/}
{INT_OCTAL}         {squeeze(yytext, '_'); printf("Found integer octal number: %s\n", yytext); /*TODO do convert*/}
{INT_BINARY}        {squeeze(yytext, '_'); printf("Found integer binary number: %s\n", yytext); /*TODO do convert*/}
{FLOAT}             {squeeze(yytext, '_'); printf("Found float number: %s\n", yytext); yylval.fval=atof(yytext); return FLOAT_NUMBER;}
{EXPONENT_FLOAT}    {squeeze(yytext, '_'); printf("Found exponent number: %s\n", yytext); /*TODO do convert*/}

#|\/\/              {str = ""; BEGIN(SINGLE_LINE_COMMENT);}
"/*"                {str = ""; BEGIN(MULTILINE_COMMENT);}

\'                  {str = ""; BEGIN(SINGLE_QUOTE_STRING);}
\"                  {str = ""; BEGIN(DOUBLE_QUOTE_STRING);}

"`"                 {str = ""; BEGIN(EXECUTION_OPERATOR);}



.                   {printf("Unknown character: %s\n", yytext);}


<NOT_IN_PHP_CODE>"<?"     {
                            inCode = true; 
                            BEGIN(INITIAL); 
                            printf("Found html code section: %s\n", str.c_str()); 
                            printf("Found start php code section: %s\n", yytext);
                            return START_CODE_PHP_TAG;
                          }
<NOT_IN_PHP_CODE>"<?php"  {
                            inCode = true; 
                            BEGIN(INITIAL); 
                            printf("Found html code section: %s\n", str.c_str());
                            printf("Found start php code section: %s\n", yytext);
                            return START_CODE_PHP_TAG;
                          }
<NOT_IN_PHP_CODE>[^\<\n]+ {str += yytext;}
<NOT_IN_PHP_CODE>\n       {str += yytext; lineCount += yyleng;}
<NOT_IN_PHP_CODE>\<+[^?]  {str += yytext;}
<NOT_IN_PHP_CODE><<EOF>>  {printf("Found html code section: %s\n", str.c_str()); BEGIN(INITIAL);}

<SINGLE_LINE_COMMENT>[^?\n]+  {str += yytext;}
<SINGLE_LINE_COMMENT>\?[^>]   {str += yytext;}
<SINGLE_LINE_COMMENT>"?>"     {
                                inCode = false; 
                                printf("Found single-line comment: %s\n", str.c_str());
                                printf("Found end php code section: %s\n", yytext); 
                                str[0] = 0; 
                                BEGIN(NOT_IN_PHP_CODE);
                                return END_CODE_PHP_TAG;
                              }
<SINGLE_LINE_COMMENT>\n       {lineCount += yyleng; printf("Found single-line comment: %s\n", str.c_str()); BEGIN(INITIAL);}

<MULTILINE_COMMENT>[^*\n]+    {str += yytext;}
<MULTILINE_COMMENT>\n         {str += yytext; lineCount += yyleng;}
<MULTILINE_COMMENT>\*[^/]     {str += yytext;}
<MULTILINE_COMMENT>"*/"       {printf("Found multiline comment: %s\n", str.c_str()); BEGIN(INITIAL);}

<EXECUTION_OPERATOR>[^`]+     {str += yytext;}
<EXECUTION_OPERATOR>"`"       {printf("Found shell command: %s\n", str.c_str()); BEGIN(INITIAL); yylval.sval=&str; return COM_STRING;}

<SINGLE_QUOTE_STRING>[^\'\\]+   {str += yytext;}
<SINGLE_QUOTE_STRING>\\\'       {str += "\'";}
<SINGLE_QUOTE_STRING>\\         {str += "\\";}
<SINGLE_QUOTE_STRING>\'         {
                                  printf("Found string literal: %s\n", str.c_str());
                                  BEGIN(INITIAL);
                                  yylval.sval=&str;
                                  return STRING;
                                }


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
<DOUBLE_QUOTE_STRING>\\[^nrtvefu"$\\]        {str += yytext;}
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
<DOUBLE_QUOTE_STRING>\\u[^{]*                 {str += yytext;}
<DOUBLE_QUOTE_STRING>\\u\{[^}]*               {str += yytext;}
<DOUBLE_QUOTE_STRING,SINGLE_QUOTE_STRING>\\\\        {str += "\\";}
<DOUBLE_QUOTE_STRING,SINGLE_QUOTE_STRING><<EOF>>     {error_print("Unclosed string", lineCount, false);}
<DOUBLE_QUOTE_STRING>\{[^$]                          {str += yytext;}
<DOUBLE_QUOTE_STRING>\{\$                     {
                                                printf("Found string %s\n", str.c_str());
                                                printf("Found concatenation: .\n");
                                                printf("Found operation: $\n");
                                                nestingCount++;
                                                BEGIN(INITIAL);
                                                yylval.sval=&str;
                                                return STRING;
                                              }
<DOUBLE_QUOTE_STRING>\$[^a-zA-Z_]?            {str += yytext;}
<DOUBLE_QUOTE_STRING>\${IDENTIFIER}           {
                                                error_print("Non supported interpolation", lineCount, true);
                                                str += yytext;
                                              }
<DOUBLE_QUOTE_STRING>\" { 
    if (nestingCount > 0){
        error_print("Unclosed interpolation", lineCount, false);
    }
    printf("Found string literal: %s\n", str.c_str());
    BEGIN(INITIAL);
    yylval.sval=&str;
    return STRING;
}

%%

/* std::string GRAPH_STR; */

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

  /* while (yylex() != 0); */
  yyparse();

  fclose(file);

  GRAPH_STR += "}";
  file = fopen("graph.dot", "w");
  fputs(GRAPH_STR.c_str(), file);
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