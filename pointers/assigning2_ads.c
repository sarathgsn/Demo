#include<stdio.h>

fun( int a[])
{
  printf("sizeof fun a = %d\n", sizeof(a)/sizeof(int));
        printf("%d\n", sizeof(a));
//  printf("%d", a[-2]);
}





int main()
{
	int a[5] = {1,2,3,4,10};
  printf("sizeof main = %d\n", sizeof(a)/sizeof(int));
        printf("%d\n", sizeof(a));

	fun(a+4);
       }
