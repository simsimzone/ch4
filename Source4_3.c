#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

/* reverse polish calculator */

/*
 * Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator. 
 * Add the modulus (%) operator and provisions for negative numbers.
 */
main()
{
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF)
	{
		switch (type)
		{
		case NUMBER:
			push(atof(s));
			break;
		case '%': /* modulus operation*/
			op2 = pop();
			push(fmod(pop(), op2));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero division");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
}

#define MAXVAL 100

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error : stack empty\n");
		return 0.0;
	}
}



#include <ctype.h>

int getch();
void ungetch(int);

int getop(char s [])
{
	int i, c;
	int nextChar;
	while ((s[0] = c = getch()) == ' ' || c == '\t');

	s[1] = '\0';
	
	if (!isdigit(c) && c != '.' && c!='-' && c!='+')
		return c;
	i = 0;
	if(c == '-' || c == '+')
	{
		nextChar = getch();
		if (!isdigit(nextChar) && nextChar != '.')//not a number, just normal minus
		{
			ungetch(nextChar);
			return c;
		}
		// we are facing a signed number.
		s[1] = c = nextChar;
		i=1;
	}

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));
	if (c == '.')
		while (isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch()
{
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}