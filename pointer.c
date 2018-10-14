#include <stdio.h>

void fun(char *ptr)
{
	int num = ptr[0] - '0';
	printf("%d\n",ptr[0]);
}




int  main()
{
	fun("123");
}
 
