#include<stdio.h>


int main()
{
 int *ptr;
 int *ptr1;
  ptr = malloc(10);
  printf("%p before realloc\n",ptr);
  ptr1 = malloc(100);
  ptr =  realloc(ptr,15);
  printf("%p before realloc\n",ptr);
}
