#include <stdio.h>

int main()
{
	int a, b, c;
	scanf("%d%d", &a, &b);
	if(b == 0)
		fprintf(stderr, "Divide by zero.\n");
	else
	{
		c = a / b;
		printf("result = %d\n", c);
	}
	return 0;
}

