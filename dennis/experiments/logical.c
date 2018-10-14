
#include<stdio.h>

int main()
{
	int a = 5, b = 3;

	if ( (a < 3 ) || ( ++b < 4))
		printf("true %d\n",b);
	else 
		printf("false\n");

}
