/* Reverse polish notation calculator */

%{
#include <stdio.h>
#include <math.h>
#include <ctype.h>
int yylex (void);
void yyerror (char const *);
%}

%union {
    double val;
}

%token <val> NUM
%type <val> exp

%% /* Grammar rules and actions follow. */

input:
|   input line
;

line:
    '\n'
|   exp '\n'    {printf ("%.10g\n", $1);}
;

exp:
    NUM         {$$ = $1;          }
|   exp exp '+' {$$ = $1 + $2;      }
|   exp exp '-' {$$ = $1 - $2;      }
|   exp exp '*' {$$ = $1 * $2;      }
|   exp exp '/' {$$ = $1 / $2;      }
|   exp exp '^' {$$ = pow ($1, $2); }
|   exp 'n'     {$$ = -$1;         }
;
%%

/* The lexical analyzer */

int yylex (void)
{
    int c;

    /* Skip white space */
    while((c = getchar()) == ' ' || c == '\t')
        continue;
    /* Process numbers */
    if(c == '.' || isdigit (c))
    {
        ungetc (c, stdin);
        scanf ("%lf", &yylval.val);
        return NUM;
    }
    /* Return end-of-imput */
    if (c == EOF)
        return 0;
    /* Return a single char */
    return c;
}

int main (void)
{
    return yyparse ();
}

void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}
