%option noyywrap nounput noinput yylineno never-interactive
%{
#include <stdio.h>
FILE* output;
%}
%%
"isalpha"     { fprintf(output, "<%d, ISALPHA, %s>\n", yylineno, yytext); }
"isdigit"     { fprintf(output, "<%d, ISDIGIT, %s>\n", yylineno, yytext); }
[1-9][0-9]    { fprintf(output, "<%d, NUMBER, %s>\n", yylineno, yytext); }
[ \t\r\n]+   ;
.             { fprintf(output, "<%d, UNKNOWN, %s>\n", yylineno, yytext); }
%%
int main() {
    yyin = fopen("../input.txt", "rb");
    output = fopen("../output_flex.txt", "w");
    if (!yyin || !output) {
        puts("File error");
        return 1;
    }
    yylex();
    fclose(yyin);
    fclose(output);
    puts("Done: output_flex.txt");
    return 0;
}
