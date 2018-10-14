#include<stdio.h>

void towerof_hanoi(int, char, char, char);
int main(void) 
{
    int n = 2;
    towerof_hanoi(n,'a', 'b', 'c');

    return 0;
}

void towerof_hanoi(int n, char src, char dest, char aux)
{
    int temp;
    int temp1, temp2;

    while( n >= 1)
    {   
        n--;
        if ( n == 1)
        {   
           temp = dest;
            dest = aux;
            aux = temp;
            printf("\n move from %c to %c  \n",src, dest);
        } 
        
    }
    printf("\n move from %c to %c  \n", src, dest);
}
