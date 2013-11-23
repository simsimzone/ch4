#include <stdio.h>
/*
 * Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the string s in place.
 */

void reverse(char s [])
{
	static int len = 0; /*just to get the length implicitly.*/
	int i = len++;
	char c = s[i];
	if (s[i] == '\0')
		return;
	reverse(s);
	s[len - i - 2] = c;
}

void main()
{
	char s[] = "sami abdelgadir";
	reverse(s);
	printf("%s\n", s);
	getchar();
}