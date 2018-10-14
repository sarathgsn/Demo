#include"../header/header.h"

int delete(struct hash *node, int key)
{

    int res;
    res = hashValue(key);

    if (node[res].data == 0 && node[res].next == NULL)
        return -1;
    else if (node[res].next == NULL)
    {
        if(node[res].data == key) {
            node[res].data = 0;
            return 1;
        } else 
            return -1;
    } else
    {
        if(node[res].data == key) {
            node[res].data = 0;
             return 1;
        } else 
        {

        struct node *temp = (struct node *) node[res].next;
        
        if(temp -> link == NULL)
        {
            if(temp -> data == key){
                temp -> data = 0;
            //    temp ->link = NULL;
                temp = NULL;
                node[res].next = (struct hash *) temp;
                return 1;
            }
            else 
                return -1;
        }

        struct node *ptr = temp;
        struct node *str  = NULL;
        while(ptr != NULL)
        {
            if (ptr ->data == key)
            { 
               str -> link = ptr -> link;
               ptr = NULL;
             
             //  node[res].next = (struct hash*) ;
               return 1;
            }
            str = ptr;
            ptr = ptr -> link;

            }
        return -1;
    }
}
}
