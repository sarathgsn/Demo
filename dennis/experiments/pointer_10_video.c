#include <stdio.h>



int main()
{
	int *ptr[10];
	int var = 100;
	int i ;
	for(i = 0 ; i < 10; i ++ )
	{
		ptr[i] = malloc(sizeof(int));
		printf("0x%08x\n",ptr[i]);
	}
	for(i = 0 ; i <10; i++)
	{
		strcpy(ptr[i],"hello");
	}
	for (i = 0 ; i  < 10; i++)
	{
		printf("0x%08x\n",ptr[i]);
		printf("%s\n",ptr[i]);
	}
}
