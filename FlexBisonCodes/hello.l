%{ 
	#undef yywrap 
	#define yywrap() 1 
%} 
%% 
[\n] { 
	printf("Hello World\n"); 
} 
%% 
 
void main() 
{ 
	yylex();  
} 

