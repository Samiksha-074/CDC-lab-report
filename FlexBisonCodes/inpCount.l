%{ 
#undef yywrap 
#define yywrap() 1  
int nlines,nwords,nchars; 
%} 

%% 
[\n] { nchars++;nlines++; } 
[^ \n\t]+ { nwords++, nchars=nchars+yyleng; } 
. { nchars++; } 
%% 


void main()  
{ 
yylex(); 
printf("Lines = %d\nChars = %d\nWords = %d",nlines,nchars,nwords); 
} 