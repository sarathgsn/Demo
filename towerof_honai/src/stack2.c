#include"../header/header_towersof_honai.h"  
int push_stack2(int element)
{

    if ( top_stack2 == stack2_size -1 )
    {
        return 0;
    } else {
        ++top_stack2;
        stack2[top_stack2] = element;
    }
}

int pop_stack2()
{
    int data;

    if ( top_stack2 == -1)
    {
        return 0;
    } else {
        data = stack2[top_stack2];
        top_stack2--;
        return data;
    }
}
int display_stack2()
{

    int i = 0;

    for ( i = top_stack2 ; i >= 0; --i)
    {
        printf("\n elemenet is %d \n",stack2[i]);
    }
} 
