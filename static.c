#include<stdio.h>
fun1(int *ptr)
{
	printf("%d\n",*ptr);
}

fun()
{
	int  x =10;
	fun1(&x); 
}

int main()
{

	fun();
	return 0;
}
