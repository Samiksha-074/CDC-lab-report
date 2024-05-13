%{
#undef yywrap
#define yywrap() 1

#include <stdio.h>
#include <stdlib.h> // Include <stdlib.h> for atof function

int f1 = 0, f2 = 0;
char oper;
float op1 = 0, op2 = 0, ans = 0;

void eval();
%}

%%

[0-9]+(\.[0-9]+)? { // Pattern for numbers
    if (f1 == 0) {
        op1 = atof(yytext); // Convert string to float
        f1 = 1;
    } else if (f2 == -1) {
        op2 = atof(yytext); // Convert string to float
        f2 = 1;
    }

    if (f1 == 1 && f2 == 1) {
        eval();
        f1 = 0;
        f2 = 0;
    }
}

[*/+-] { // Pattern for operators
    oper = *yytext;
    f2 = -1;
}

[\n] {
    // Ignore newlines
}

%%

int main() {
    yylex();
    return 0;
}

void eval() {
    switch (oper) {
        case '+':
            ans = op1 + op2;
            break;

        case '-':
            ans = op1 - op2;
            break;

        case '*':
            ans = op1 * op2;
            break;

        case '/':
            if (op2 == 0) {
                printf("ERROR: Division by zero\n");
                return;
            } else {
                ans = op1 / op2;
            }
            break;

        default:
            printf("ERROR: Operation not recognized\n");
            return;
    }
    printf("The answer is = %f\n", ans); // Use %f for float
}
