#include<stdio.h>

#define SAR
#define R
int main()
{
#if defined(SAR) && defined(R)
printf("hello\n");
#endif 

}


