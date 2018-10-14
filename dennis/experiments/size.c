#include<stdio.h>

int main()
{
	char *ptr = "hello";
	printf("%d\n",sizeof(ptr));
	printf("%d\n",sizeof(*ptr));
	return 0;
}
