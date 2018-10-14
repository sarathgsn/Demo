#include"../header/header_towersof_honai.h"  
int push_stack3(int element)
{

    if ( top_stack3 == stack3_size -1 )
    {
        return 0;
    } else {
        ++top_stack3;
        stack3[top_stack3] = element;
    }
}

int pop_stack3()
{
    int data;

    if ( top_stack3 == -1)
    {
        return 0;
    } else {
        data = stack3[top_stack3];
        top_stack3--;
        return data;
    }
}
int display_stack3()
{

    int i = 0;

    for ( i = top_stack3 ; i >= 0; --i)
    {
        printf("\n elemenet is %d \n",stack3[i]);
    }
}
