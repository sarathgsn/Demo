#include <stdio.h>


int main()
{
	char *ptr = "globaledge";
	char str[] = "globaledge";
	printf("0x%8x\n",ptr);
	printf("%p\n",str);
}
