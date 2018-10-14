

#include<stdio.h>


int  fun()
{
  int x = 100 ;
  int y = 200;
   int z = x + y * ( x + 50);
 return z;
}

int main()
{
  int x;
  printf("hello world\n");
  x = fun();
  printf("%d\n",x);
}
