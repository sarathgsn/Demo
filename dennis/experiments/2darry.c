#include<stdio.h>


fun(int *ptr[])
{
printf("%p\n",ptr);
printf("%p\n",*ptr);
}




int main()
{
	int a[][3] = { 1,2,3};
	printf("%p\n",a);
	fun(&a);
}
