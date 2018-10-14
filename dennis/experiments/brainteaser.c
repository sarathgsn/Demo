#include<stdio.h>

int * foo()
{ int x = 10;
  return &x;
}

void bar()
{
int c = 888;
}




int main()
{
   int *ptr = foo();
	printf("%p\n",ptr);
//   bar();
	printf("%p\n",ptr);
  printf("%d\n",*ptr);
}
