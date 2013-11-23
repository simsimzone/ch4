#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

char pattern [] = "ould";

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

/* strLastIndex: returns the last index of t in s, -1 if none */
int strLastIndex(char s [], char t [])
{
	int lenS, lenT;
	int i, j, k;
	lenS = strlen(s);
	lenT = strlen(t);
	for (i = lenS - 1; i > 0; i--)
	{
		for (j = i, k = lenT - 1; k >= 0 && s[j] == t[k]; j--, k--);
		if (k < 0)
			return j + 1;
	}
	return -1;
}



//Exercise 4-1. Write the function strindex(s,t) which returns the position of the rightmost occurrence of t in s, 
//or -1 if there is none.
void ex4_1()
{
	char line[MAXLINE];
	int index = 0, i;
	while (getline(line, MAXLINE) > 0)
		if ((index = strLastIndex(line, pattern)) >= 0) {
			for (i = 0; i < index; i++)
				printf(" ");
			printf("^\n");
		}
		else
			printf("key not found...\n");
}

main()
{
	ex4_1();
	getchar();
}