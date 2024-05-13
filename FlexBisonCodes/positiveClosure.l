%{
#include <stdio.h>
int getch(); // Declare getch() function
%}

%option noyywrap

%%

.*11.* {
    printf("\nIt is a positive closure = ");
    ECHO;
return 0;
}

.+ {
    printf("\nNot a positive closure = ");
    ECHO;
    getch(); // Move getch() here
    return 0; // Return an integer value
}

%%

int main() // Change void main() to int main()
{
    printf("Enter a string: ");
    yylex();
    return 0; // Add return statement
}

int getch() // Define getch() function
{
    return getchar(); // Simply return getchar() for now
}
