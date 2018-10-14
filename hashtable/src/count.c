#include"../header/header.h"

int count(struct hash *node, int key)
{   
    int count = 0;
    int res;
    res = hashValue(key);


    if(node[res].data == 0 && node[res].next == NULL)
    {

        return count;
    }
    else if(node[res].next == NULL) {
        if( node[res].data != 0) {
            count++;
            return count;
        } 
    }
    else
    {  
       if(node[res].data != 0)
           count++; 

        struct node *temp = (struct node *) node[res].next;
        while( temp != NULL) 
        {
            count++;
            temp = temp->link;
        }
        return count;
       
    }
}


