#include<stdio.h>

int main()
{
  int a[] = {10,20,30};
  int *ptr = a;
  printf(" %d %d\n", *ptr,*ptr++);
  printf("%d\n",a);
}
