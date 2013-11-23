/*
 *
 *                                      reverse polish calculator
 *                                  CODED BY: ENG. SAMI ABDELGADIR MOHAMMED
 *
 *
 * Exercise 4-6. Add commands for handling variables.
 * (It's easy to provide twenty-six variables with single-letter names.)
 * Add a variable for the most recently printed value.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP           100
#define MAXERROR        30
#define NUMBER          '0'
#define OPERATOR        '1'
#define COMMAND         '2'
#define UNARY_FUNCTION  '3'
#define BINARY_FUNCTION '4'
#define VARIABLE        '5'
#define ASSIGNER        '6'
#define ERROR           '7'

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
void emptybuffer();
void push(double);
double pop(void);
int canPop();
void stackCommands(int);
void emptybuffer();

int underCommand = 0;
double vars[27];
int assigner = 0;
int index = -1;
char err[30];

double unaryFunc(char s [], double arg)
{
	if (isEqual(s, "sin"))
		return sin(arg);
	else if (isEqual(s, "cos"))
		return cos(arg);
	else if (isEqual(s, "tan"))
		return tan(arg);
	else
		return 0.0;
}

double binFunc(char s [], double arg1, double arg2)
{
	if (isEqual(s, "pow"))
		return pow(arg1, arg2);
	else
		return 0.0;
}

double op(double v1, char op, double v2)
{
	switch (op)
	{
	case '+':
		return v1 + v2;
		break;
	case '-':
		return v1 - v2;
		break;
	case '*':
		return v1 * v2;
		break;
	case '/':
		if (v2 != 0.0)
			return v1 / v2;
		else
			printf("error: zero division");
		return 0.0;
		break;
	case '%':
		return fmod(v1, v2);
		break;
	default:
		printf("Unknown operator");
		return 0.0;
		break;
	}
}

/*we only take one letter as a variable name*/
void setVariable(char s [], double val)
{
	if (isEqual(s, "ans") || isEqual(s, "Ans"))
		vars[26] = val;
	else
		vars[s[0] - 'a'] = val;
}

double getVariable(char s [])
{
	if (isEqual(s, "ans") || isEqual(s, "Ans"))
		return vars[26];
	return vars[s[0] - 'a'];
}

void rpnError(char err[], int index)
{
	while (index-- > 0)
		putchar(' ');
	printf("^ error, %s\n", err);
	emptybuffer();
	stackCommands('C');
	underCommand = 0;
}

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
		case ASSIGNER:
			assigner = 1;
			break;
		case VARIABLE:
			if (assigner)
			{
				push(op2 = pop());
				setVariable(s, op2);
				assigner = 0;
			}
			else
			{
				push(getVariable(s));
			}
			break;
		case OPERATOR:
			op2 = pop();
			push(op(pop(), s[0], op2));
			break;
		case '\n':
			if (assigner)
			{
				index--;
				rpnError("No variable to assign to.", index);
				index = -1;
				assigner = 0;
				break;
			}
			if (!underCommand && canPop())
			{
				push(op2 = pop());
				setVariable("ans", op2);
				stackCommands('T');
				stackCommands('C'); /* empty stack and start a new line. */
			}
			underCommand = 0;
			index = -1;
			break;
		case ERROR:
			rpnError(err, index);
			index = -1;
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

int canPop()
{
	return sp;
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
	}
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
#include <string.h>

int getch();
void ungetch(int);

int isNumber(char s [])
{
	int i = 0, c, nextChar;
	c = s[0];
	if (c == '-' || c == '+')
	{
		nextChar = getch();
		if (!isdigit(nextChar) && nextChar != '.') /* not a number, just normal minus or plus. */
		{
			ungetch(nextChar);
			return 0;
		}
		/* we are facing a signed number. */
		s[++i] = c = nextChar;
	}
	if (!isdigit(c) && c != '.')
		return 0;
	while (isdigit(s[++i] = nextChar = getch())); /* read the integer part, or maybe the decimal part. */
	s[i] = '\0';
	if (nextChar == '.')
	{
		s[i] = '.';
		s[++i] = '\0';
		if (c == '.')
		{
			strcpy_s(err, MAXERROR, "two decimal points");
			return ERROR;
		}
		while (isdigit(s[i++] = c = getch()));/* read the decimal part. */
		if (c == '.')
		{
			s[i] = '\0';
			strcpy_s(err, MAXERROR, "not a number");
			return ERROR;
		}
		s[--i] = '\0'; /* replace the last non digit by '\0' */
		nextChar = c;
	}
	else if (nextChar != ' ' && nextChar != '\n' && nextChar != EOF)
	{
		strcpy_s(err, MAXERROR, "not a number");
		return ERROR;
	}
	if (nextChar != EOF)
		ungetch(nextChar);
	return NUMBER;
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
	strcpy_s(err, MAXERROR, "function not found...!");
	/*while (i > 1)
		ungetch(s[--i]);*/
	return ERROR;
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

int isAssigner(char s [])
{
	int nextChar;
	if (s[0] == '-')
	{
		nextChar = getch();
		if (nextChar != '>')
		{
			ungetch(nextChar);
			return 0;
		}
		return 1;
	}
	return 0;
}

int isVariable(char s [])
{
	int i = 0, c = s[0];
	if (!isalpha(c))
		return 0;
	while (isalpha(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	if (i == 1)// variable a-z
		return 1;
	if (isEqual(s, "ans") || isEqual(s, "Ans"))
		return 1;
	while (i > 1)
		ungetch(s[--i]);
	return 0;
}

int isOperator(char s [])
{
	switch (s[0])
	{
	case '+':case '-':case '*':case '/':case '%':
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
	res = isNumber(s);
	if (res)
		return res;
	if (isAssigner(s))
		return ASSIGNER;
	if (isVariable(s))
		return VARIABLE;
	if (isOperator(s))
		return OPERATOR;
	res = isFunction(s);
	if (res)
		return res;
	if (s[0] == '\n')
		return '\n';
	if (c == EOF)
		return EOF;
	return ERROR;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch()
{
	index++;
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	index--;
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* consume the remaining unread characters. */
void emptybuffer()
{
	char c;
	while ((c = getch()) != EOF && c != '\n');
}