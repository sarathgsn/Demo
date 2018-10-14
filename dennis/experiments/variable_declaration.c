#include<stdio.h>

int main()
{       
	int a = 199;
	int *p = NULL;
	{
		int a = 10;
		p = &a;
	}
	printf("%d\n", *p);
}
