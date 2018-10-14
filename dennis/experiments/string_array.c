#include<stdio.h>

int main()
{
	char a[10] = {1,2,3};
	char *ab = "hello";
	char *b = (char *)(ab - a) ;
	printf("%c\n",*b);

}
