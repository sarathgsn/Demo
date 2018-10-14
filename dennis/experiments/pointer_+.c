#include<stdio.h>

int main()
{
	int x = 100;
	int *ptr = &x;
	printf("%d\n", ++*ptr);
	printf("%d\n", *ptr++);
	printf("%d\n", *ptr++);
	
}
