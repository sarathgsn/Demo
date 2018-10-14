#include"../header/header.h"

int search(char *key, struct hash *node)
{
    int res;
    int retu;
    char a[10];
//    strcpy(a, key);
    res = hashValue(key);

    if ( node[res].data  == NULL && node[res].next == NULL) {
         return -1;
    } else if (node[res].next == NULL) {

        retu = strcmp( node[res].data , key);
            if ( retu == 0)
            return 1;
        }
    

    else  
    {   
       // if (node[res].data == key)

        retu = strcmp( node[res].data , key);
            if ( retu == 0){
            return 1;
        //    return 1;
            } else {
        struct node *temp = (struct node *) node[res].next;
        
        while (temp != NULL)
        {   
            retu = strcmp(temp->data, key);
            if( retu == 0)
                 return 1;

            temp = temp -> link;
        }

        }
    }


    return -1;
}

