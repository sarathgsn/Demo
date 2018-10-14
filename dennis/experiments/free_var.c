#include<stdio.h>

int main()
{
  int var = 10;
	free(&var);
	printf("%p\n",&var);
}
