#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

int getline(char s [], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* atof: convert string s to double */
double atof(char s [])
{
	double val, power;
	int i, sign, expsign, exp;
	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if (s[i] == 'e' || s[i] == 'E')
	{
		i++;
		//we have to read an int number
		expsign = (s[i] == '-') ? -1 : 1;
		if (s[i] == '-' || s[i] == '+')
			i++;
		for (exp = 0; isdigit(s[i]); i++)
			exp = 10 * exp + (s[i] - '0');
		//now we don't need i any more, we can use it..
		for (i = 0; i < exp; i++)
			power = expsign>0 ? power / 10.0 : power * 10.0;
	}
	return sign * val / power;
}

//Exercise 4-2. Extend atof to handle scientific notation of the form
//123.45e-6
//where a floating - point number may be followed by e or E and an optionally signed exponent.
void ex4_2()
{
	double sum;// , atof(char []);
	char line[MAXLINE];
	//int getline(char line [], int max);
	sum = 0;
	while (getline(line, MAXLINE) > 0)
		printf("\t%g\n", sum += atof(line));
}

main()
{
	ex4_2();
	getchar();
}