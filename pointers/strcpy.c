
#include<stdio.h>

int* mystrcpy(char *src, char *des)
{
 //   des = src;
    return src;
}


int main(void) 
{


    char src[10] = "hello";
    char *des[10];
   char *ptr;
  des[0] =  mystrcpy(src,des);
  printf("\n %s  \n", des[0]);
  return 0;
}
