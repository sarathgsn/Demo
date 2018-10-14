#include<stdio.h>


int main()
{
	void *ptr;
	int x = 100;
	ptr = &x;
	printf("%d",*((int *)ptr));
}
