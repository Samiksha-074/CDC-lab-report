%{
	#undef yywrap
	#define yywrap() 1
	#include <stdio.h> // Include stdio.h for getch() function
	void display(int);
%}

%%

[a|e|i|o|u|] {
	int flag=1;
	display(flag);
	return 1; // Return an integer value
}

.+ {
	int flag=0;
	display(flag);
	return 0; // Return an integer value
}

%%

void display(int flag)
{
	if(flag==1)
		printf("The given letter [%s] is a vowel",yytext);
	else
		printf("The given letter [%s] is NOT a vowel",yytext);
	getchar(); // Change getch() to getchar()
}

int main() // Change void main() to int main()
{
	printf("Enter a letter to check if it is a vowel or not: ");
	yylex();
	
}
