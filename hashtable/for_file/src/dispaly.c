#include"../header/header.h"

void display(struct hash *node, int key)
{
    if (node[key].data == 0 && node[key].next == NULL)

        printf("\n no elements  are available in this key \n");

    else if ( node[key].data != 0  &&  node[key].next == NULL) {

        printf("\n  only one element is = %d \n", node[key].data);

    } else 
    {
        if ( node[key].data != 0)
            printf("\n data is %d  \n", node[key].data);
        
        
            struct node *temp = (struct node *) node[key].next;

            while( temp != NULL)
            {
                printf("\n data is  %d \n", temp -> data);
                temp = temp -> link;
            }
        
    }
}


