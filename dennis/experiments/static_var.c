#include<stdio.h>
static int x = 200;
#if 0
void fun()
{
	int local_var;
	static int x = 100;
	local_var = x;
	printf("%d\n",x++);

}



int main()
{
	int i = 0;
	register int  b ;
	b = 10;
	for (i = 0; i < 5 ;i++)
	{ 
		fun();
	}
}
#endif 

int main()
{
	int local;
	printf("%p\n",&x);
	printf("%d\n",x);
	static int x = 100;
	register int loca_reg;

	printf("%p\n",&x);
	printf("%d\n",x);
//	x = 5;
	local = 6;
//	x = 7;
	loca_reg = 8;
}
