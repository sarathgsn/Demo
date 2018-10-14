#include<stdio.h>

int main(void) 
{
    struct a {
        int a ;
        int b;
    } b  = { 12, 33};

    struct a *a = &b;
    (*a).a;
//    printf("\n *a.a = %d  \n",(*a).a );
    printf("\n a.a = %d \n",++a->a);

    return 0;
}

