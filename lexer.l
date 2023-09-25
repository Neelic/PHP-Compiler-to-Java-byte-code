%option noyywrap
%option never-interactive
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%{
// Define the token types
#define TOKEN_VAR 1
#define TOKEN_FUNCTION 2
#define TOKEN_IF 3
#define TOKEN_ELSE 4
#define TOKEN_WHILE 5
#define TOKEN_ECHO 6
#define TOKEN_STRING 7
#define TOKEN_NUMBER 8

// Helper function to handle tokens
void handleToken(int tokenType, const char* lexeme) {
switch(tokenType) {
case TOKEN_VAR:
printf("Variable: %s\n", lexeme);
break;
case TOKEN_FUNCTION:
printf("Function: %s\n", lexeme);
break;
case TOKEN_IF:
printf("If statement\n");
break;
case TOKEN_ELSE:
printf("Else statement\n");
break;
case TOKEN_WHILE:
printf("While loop\n");
break;
case TOKEN_ECHO:
printf("Echo statement\n");
break;
case TOKEN_STRING:
printf("String: %s\n", lexeme);
break;
case TOKEN_NUMBER:
printf("Number: %s\n", lexeme);
break;
default:
printf("Unknown token\n");
}
}
%}

%%

\$[a-zA-Z_][a-zA-Z0-9_]* { handleToken(TOKEN_VAR, yytext); }
[a-zA-Z_][a-zA-Z0-9_]*\( { handleToken(TOKEN_FUNCTION, yytext); }
if { handleToken(TOKEN_IF, NULL); }
else { handleToken(TOKEN_ELSE, NULL); }
while { handleToken(TOKEN_WHILE, NULL); }
echo { handleToken(TOKEN_ECHO, NULL); }
\"[^\"]*\" { handleToken(TOKEN_STRING, yytext); }
[0-9]+ { handleToken(TOKEN_NUMBER, yytext); }
\n { /* Ignore newline */ }

. { /* Ignore all other characters */ }
%%

int main(void) {
yyin = fopen("example.php", "r");

// Call the lexer
yylex();

fclose(yyin);
return 0;
}