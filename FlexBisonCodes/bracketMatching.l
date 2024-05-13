%{
#undef yywrap
#define yywrap() 1
int flag = 0;
%}

%%

"(" { 
    flag++;
}

")" { 
    flag--;
}

[\n] { 
    if(flag == 0)
        printf("\n The statement has no missing parenthesis\n\n");
    else if(flag > 0)
        printf("\n The statement has either extra ( parenthesis or a missing ) parenthesis\n\n");
    else if(flag < 0)
        printf("\n The statement has either extra ) parenthesis or a missing ( parenthesis\n\n");
    
    flag = 0;
}

%%

int main() 
{  
    yylex(); 
    return 0; 
}
