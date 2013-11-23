/*
Exercise 4-11. Modify getop so that it doesn't need to use ungetch. Hint: use an internal static variable.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

/* reverse polish calculator */
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
			push((int) pop() % (int) op2);
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
	static int lc = 0;
	if (lc != 0)
	{
		c = lc;
		lc = 0;
	}
	else
		c = getch();
	while ((s[0] = c) == ' ' || c == '\t') /* skip spaces. */
		c = getch();

	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c;
	i = 0;

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));
	if (c == '.')
		while (isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
	{
		lc = c;
		//ungetch(c);
	}
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch()
{
	return bufp > 0 ? buf[--bufp] : getchar();
}

/*
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
*/