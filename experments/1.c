#include<stdio.h>
#include<time.h>

int main(void) 

{
    clock_t begin = clock();

    /* here, do your time-consuming job */


printf("\n  hello \n");
printf("\n hai  \n");

int i = 0;
while( i < 1000)
{
    i++;
}







    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\n end  %lf  \n",time_spent );
printf("\n begin   \n");
    return 0;
}
