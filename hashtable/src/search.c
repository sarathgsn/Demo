#include"../header/header.h"

int search(int key, struct hash *node)
{
    int res;
    res = hashValue(key);

    if ( node[res].data  == 0 && node[res].next == NULL) {
         return -1;
    } else if (node[res].next == NULL) {

        if ( node[res].data == key) {
            return 1;
        }
    }

    else  
    {   
        if (node[res].data == key)
            return 1;
        else {
        struct node *temp = (struct node *) node[res].next;
        
        while (temp != NULL)
        {   
            if( temp -> data == key)
                 return 1;

            temp = temp -> link;
        }

        }
    }


    return -1;
}

