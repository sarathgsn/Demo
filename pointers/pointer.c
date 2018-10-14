#include<stdio.h>



fun(int *a)
{
   *( a+4) = 100;
}







int main(void)
{ 
  
    int a[10] = { 1,2,3,4,5};
    fun(a);
    printf("\n  %d \n", a[4]);
    return 0;
}
