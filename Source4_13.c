#include <stdio.h>
/*
 * Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the string s in place.
 */

void reverse(char s [])
{
	static int len = 0; /*just to get the length implicitly.*/
	int i = len;
	char c = s[i];
	if (s[i] == '\0')
		return;
	len++;
	reverse(s);
	s[len - i - 1] = c;
	if (i == 0)
		len = 0;
}

void main()
{
	char s[] = "kkk", ss[] = "sami";
	reverse(s);
	printf("%s\n", s);
	reverse(ss);
	printf("%s\n", ss);
	reverse(ss);
	printf("%s\n", ss);
	getchar();
}