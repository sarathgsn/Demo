#include<stdio.h>
#if 0
int main()
{
	const const const volatile volatile int local_var = 10;
//        printf("%d\n",a);
}
#endif 


#if  1

   const static int global_var = 10;
int main()
{

 int *ptr = &global_var;
	*ptr = 3000;
	printf("%d\n",*ptr);
}

#endif 
