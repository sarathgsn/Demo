
#include"../header/header_towersof_honai.h"
int push_stack1(int element)
{

    if ( top_stack1 == stack1_size -1 )
    {
        return 0;
    } else {
        ++top_stack1;
        stack1[top_stack1] = element;
    }
}

int pop_stack1()
{
    int data;

    if ( top_stack1 == -1)
    {
        return 0;
    } else {
        data = stack1[top_stack1];
        top_stack1--;
        return data;
    }
}


int display_stack1()
{

    int i = 0;

    for ( i = top_stack1 ; i >= 0; --i)
    {
        printf("\n elemenet is %d \n",stack1[i]);
    }
} 
