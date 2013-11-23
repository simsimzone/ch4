#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP           100
#define NUMBER          '0'
#define COMMAND         '1'
#define UNARY_FUNCTION  '2'
#define BINARY_FUNCTION '3'


/* isEqual: checks whether cnst string equals s string. */
int isEqual(char s [], char cnst [])
{
	int i = 0;
	while (s[i] == cnst[i])
	{
		if (s[i++] == '\0')
			return 1;
	}
	return 0;
}
int getop(char []);
void push(double);
double pop(void);

void stackCommands(int);
int underCommand = 0;

double unaryFunc(char s[], double arg)
{
	if (isEqual(s, "sin"))
		return sin(arg);
	else if (isEqual(s, "cos"))
		return cos(arg);
	else if (isEqual(s, "tan"))
		return tan(arg);
	else
	{
		printf(" error: unknown function.\n");
		return 0.0;
	}
}

double binFunc(char s [], double arg1, double arg2)
{
	if (isEqual(s, "pow"))
		return pow(arg1, arg2);

	printf("error: unknown function");
	return 0.0;
}

/* reverse polish calculator */
/* 
 * Exercise 4-5. Add access to library functions like sin, exp, and pow. See <math.h> in Appendix B, Section 4.
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
		case COMMAND:
			stackCommands(s[0]);
			break;
		case UNARY_FUNCTION:
			push(unaryFunc(s, pop()));
			break;
		case BINARY_FUNCTION:
			op2 = pop();
			push(binFunc(s, pop(), op2));
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
			if (!underCommand)
				stackCommands('T');
			else
				underCommand = 0;
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

/* P */
void printStack()
{
	int i;
	if (sp)
	{
		for (i = 0; i < sp - 1; i++)
			printf("%.3g,", val[i]);
		printf("%.3g\n", val[sp - 1]);
	}
}

/* T */
void printTopElements(int n)
{
	int i;
	if (sp)
		putchar('\t');
	for (i = sp - 1; i > 0 && n > 1; i--, n--)
		printf("%.3g,", val[i]);
	if (n && sp)
		printf("%.3g\n", val[i]);
	else
		printf("no top elements in the stack to print out.\n");
}

/* D */
void duplicate()
{
	double d;
	if (sp)
	{
		d = pop();
		push(d);
		push(d);
		printf("top element \'%.3g\' has been duplicated.\n", d);
	}
	else
		printf("no elements to duplicate.\n");
}

/* S */
void swapTopTwo()
{
	double d, c;
	if (sp > 1)
	{
		d = pop();
		c = pop();
		push(d);
		push(c);
		printf("top elements \'%.3g\' , \'%.3g\' have been swapped.\n", d, c);
	}
	else
		printf("no sufficient element to be swapped.\n");
}

/* C */
void clearStack()
{
	if (sp)
	{
		sp = 0;
		printf("stack has been cleared.\n");
	}
	else
		printf("stack is already empty.\n");
}

/* stackCommands: executes variuos commands on the stack*/
void stackCommands(int type)
{
	switch (type)
	{
	case 'P':
		printStack();
		break;
	case 'T':
		printTopElements(1);
		break;
	case 'D':
		duplicate();
		break;
	case 'S':
		swapTopTwo();
		break;
	case 'C':
		clearStack();
		break;
	default:
		break;
	}
	underCommand = 1;
}


#include <ctype.h>

int getch();
void ungetch(int);

int isNumber(char s[])
{
	int i = 0, c, nextChar;
	c = s[0];
	if (c == '-' || c == '+')
	{
		nextChar = getch();
		if (!isdigit(nextChar) && nextChar != '.')/* not a number, just normal minus. */
		{
			ungetch(nextChar);
			return 0;
		}
		/* we are facing a signed number. */
		s[++i] = c = nextChar;
	}
	if (!isdigit(c) && c != '.')
		return 0;
	while (isdigit(s[++i] = c = getch()));
	if (c == '.')
		while (isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return 1;
}

int isFunction(char s [])
{
	int i = 0, c = s[0];
	if (!isalpha(c))
		return 0;
	while (isalpha(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);

	if (isEqual(s, "sin") || isEqual(s, "cos") || isEqual(s, "tan"))
		return UNARY_FUNCTION;
	if (isEqual(s, "pow"))
		return BINARY_FUNCTION;
	while (i > 1)
		ungetch(s[--i]);
	return 0;
}

int isCommand(char s [])
{
	switch (s[0])
	{
	case 'P':case 'T':case 'D':case 'S':case 'C':
		return 1;
	default:
		return 0;
	}
}

int getop(char s [])
{
	int c, res;
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';

	if (isCommand(s))
		return COMMAND;
	if (isNumber(s))
		return NUMBER;
	res = isFunction(s);
	if(res)
		return res;
	return c;
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