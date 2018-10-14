#include<stdio.h>

int   function_unused();

int global_var;


int main()
{
	static 	int local_static ;
//	function_unused();
	int b = 100;
	return 0;
}

 int function_unused()
{
	printf("hello:");
	int global_var = 100;
	return 0;
}
