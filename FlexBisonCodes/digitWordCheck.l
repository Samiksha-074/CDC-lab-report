%{
#include <stdio.h>
void display(char[], int);
int yywrap(); // Declare yywrap
%}

%%

[a-zA-Z]+ {
    int flag = 1;
    display(yytext, flag);
    return 0;
}

[0-9]+ {
    int flag = 0;
    display(yytext, flag);
    return 0;
}

.+ {
    int flag = -1;
    display(yytext, flag);
    return 0;
}

%%

void display(char a[], int flag)
{
    if(flag == 1)
        printf("The given string = %s is a word\n", a);
    else if(flag == 0)
        printf("The given string = %s is a number\n", a);
    else if(flag == -1)
        printf("The given string = %s is something else\n", a);
    getchar();
}

int yywrap() // Define yywrap
{
    return 1; // Indicate end of input
}

int main()
{
    printf("Enter a string: ");
    yylex();
    return 0;
}
