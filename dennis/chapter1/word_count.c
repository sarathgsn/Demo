#include<stdio.h>


int main(void) 
{
    int  c, n;
    while( (c = getchar()) != EOF)
         if ( c == ' ' || c == '\n' || c == '\t')
             n++;
    printf("\n %d  \n",n);
     

}
