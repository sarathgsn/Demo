#include"../header/header.h"

int count(struct hash *node, char *key)
{   int value ;
    int count = 0;
    int res;
    res = hashValue(key);


    if(node[res].data == NULL && node[res].next == NULL)
    {

        return count;
    }
    else if(node[res].next == NULL) {

        value = strcmp(node[res].data, key);

        if( value == 0) {
            count++;
            return count;
        } 
    }
    else
    {  
        value = strcmp(node[res].data, key);
            if(value == 0) {
     /*  if(node[res].data != NULL)
       */    count++; 
            }

        struct node *temp = (struct node *) node[res].next;
        while( temp != NULL) 
        {  
        value = strcmp(temp->data, key);
           if(value == 0) {
            count++;
           }
            temp = temp->link;
        }
        return count;
       
    }
}


