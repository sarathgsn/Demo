#include<stdio.h>

int main()
{
#if 1
	int x = 10000;
	char *ptr = "hello";
	printf("%-7s\n","hello");
	printf("%8d\n","hello");
#endif 
#if 0
 printf("%-9s men","meet");
 printf("%-8s men","meet");
 printf("%-7s men","meet");
 printf("%-6s men","meet");
 printf("%-5s men","meet");
 printf("%-4s men","meet");
 printf("\n");
#endif 
}
