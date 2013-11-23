#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define swap(t,x,y) do                     \
					{                      \
						t temp##x##y;      \
						temp##x##y = (x);  \
						(x) = (y);         \
						(y) = temp##x##y;; \
					}while (0)             \

void main()
{
	int x, y;
	x = 10;
	y = 20;
	printf("x=%d, y=%d\n", x, y);
	swap(int, x, y);
	printf("x=%d, y=%d", x, y);

	getchar();
}