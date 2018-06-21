#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
int val_length();
void clear();

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0;  /* next freee stack position */

double val[MAXVAL]; /* value stack */

/* reverse Polish calculator */

int main()
{

	int type;
	double op2;
	char s[MAXOP];
	static int sign;
	double temp;

	while ((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				if ( sign == -1 )
				{
					push(-atof(s));
					sign = 1;
					break;
				}

				push(atof(s));
				break;
			case '+':
				push(pop()+pop());
				break;
			case '*':
				push(pop()*pop());
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop()/op2);
				else
					printf("error: zero divisor\n");
				break;
			case '-':
				if ( (val_length()%2 != 0) || (val_length() == 0 ) )
				{	
					sign = -1;
					break;
				}
					
				op2 = pop();
				if (op2 != 0.0)
					push(pop()-op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(),op2));
				else
					printf("error: zero divisor\n");
				break;
			case 'p':
				printf("\t%.8g\n",val[0]);
				break;
			case 'd':
				val[1] = val[0];
				break;
			case 's':
				temp = val[0];
				val[0] = val[1];
				val[1] = temp;
				break;
			case '\n':
				if (s[0] == 'p'|| s[0] == 'd' || s[0] == 's')
				{ }
				else
				{
				printf("\t%.8g\n",pop());
				}
				break;
			default:
				printf("error: unknown command %s\n",s);
				break;
		}
	}
		return 0;
}


/* push: push f onto value stack */
void push(double f)
{

	if (sp < MAXVAL)
	{
		val[sp++] = f;
	}
	else
	{
		printf("error: stack full, can't push %g\n",f);
	}

}

/* pop: and return top value from stack */
double pop(void)
{

	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0;
	}

}

#include <ctype.h>

int getch(void);
void ungetch(int);

/*getop: get next operator or numeric operand */
int getop(char s[])
{
	
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t');

	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c; 		/* not a number */
	i = 0;
	if (isdigit(c)) 		/* collect integer part */
	{
		while (isdigit(s[++i] = c = getch()));
	}
	if (c == '.')
	{
		while (isdigit(s[++i] = c = getch()));
	}
	s[i] = '\0';
	if ( c != EOF)
	{
		ungetch(c);
	}
	return NUMBER;

}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if ( bufp > BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int val_length()
{
	
	return (sp);

}

void clear()
{
	
	int i = 0;

	while (i < val_length() )
	{
		val[i++] = 0;
	}

}