%{
#include <iostream>
#include <stdio.h>
using namespace std;
int line_number = 1;
%}
%option noyywrap
DIGIT [0-9]
NUMBER [1-9]{DIGIT}
%%
[ \t\r]+ ;
\n { line_number++; }
"isalpha" { cout << "<" << line_number << ", ISALPHA, " << yytext << ">" << endl; }
"isdigit" { cout << "<" << line_number << ", ISDIGIT, " << yytext << ">" << endl; }
{NUMBER} { cout << "<" << line_number << ", NUMBER, " << yytext << ">" << endl; }
. { cout << "<" << line_number << ", UNKNOWN, " << yytext << ">" << endl; }
%%
int main() {
    if (freopen("../input.txt", "r", stdin) == NULL) {
        cout << "File error" << endl;
        return 1;
    }
    if (freopen("../output_flex.txt", "w", stdout) == NULL) {
        cout << "File error" << endl;
        return 1;
    }
    yylex();
    return 0;
}


