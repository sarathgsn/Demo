#include<stdio.h>
volatile int g_var;
int main()
{
	g_var = 5;
	while (g_var == 5)
	{
		;
}
}
