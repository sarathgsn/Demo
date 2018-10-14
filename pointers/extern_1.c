#include<stdio.h>


int main(void) 
{
    extern int max ;
    max = 400;
    fun();
  //  max = 300;
    printf("\n %d  \n", max);
    return 0;
}

fun()
{
    extern int max;
    max = 200;
    printf("\n %d  \n", max);

}
int max = 100;
