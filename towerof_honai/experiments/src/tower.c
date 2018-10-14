#include"../header/header.h"

void towerof_hanoi(int n, struct node *source, struct node *dest, struct node *temp)
{
    if(n == 1)
    {
        printf("\nMove from tower %d to %d", source -> ind, dest -> ind);
        g = pop(source);
        push(dest, g);
    }
    else
    {
        towerof_hanoi(n-1, source, temp, dest);
        printf("\nMove from tower %d to %d", source -> ind, dest->ind);
        g = pop(source);
        push(dest, g);
        towerof_hanoi(n-1, temp, dest, source);
    }
}
