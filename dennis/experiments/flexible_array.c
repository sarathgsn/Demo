#include<stdio.h>

struct a{
 int a[0];
};
int main()
{
   int n= 5;
//   int i;
   int a[n]; 
//   printf("ebter\n");
//scanf("%d",&n);

	for (int  i = 0 ; i < n; i++) 
	scanf("%d",&a[i]);
	
	for ( i = 0 ; i < n; i++)
        printf("%d",a[i]);

   
}
