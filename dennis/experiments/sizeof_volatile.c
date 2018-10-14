#include<stdio.h>
int main()
{
	int size = sizeof(volatile) + sizeof(const);
	printf("%d",-12);
	return 0;
}
