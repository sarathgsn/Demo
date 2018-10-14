#include<stdio.h>
const int a = 10;
int main()
{
 //const int a = 10;
 int *p = &a;
	*p = 100;
	printf("%d\n",*p);
	printf("%d\n",a);
}
	
