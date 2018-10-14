#include<stdio.h>

static void * fun()
{
	printf("hai hello\n");
}




int main()
{

	printf("%p\n",__builtin_return_address(0));
	fun();
}
