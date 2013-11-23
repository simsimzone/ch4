#include <stdio.h>
#include <math.h>
#include <limits.h>

#define MAX_CHARS 64

/*
 * Exercise 4 - 12. Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an integer into a string by calling a recursive routine.
 */

/*
 * itoa: converts an int number to its character representation.
 */
void itoa(int n, char s [])
{
	static int i = 0;
	if (n / 10)
		itoa(n / 10, s);
	else if (n < 0) /* else will be executed on the left most digit. */
		s[i++] = '-';
	s[i++] = abs(n % 10) + '0';
	s[i] = '\0';
}

void main()
{
	int n = INT_MIN;
	char s[MAX_CHARS];
	itoa(n, s);
	printf("%s\n", s);
	getchar();
}