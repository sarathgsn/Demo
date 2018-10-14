#include "hashing_header.h"

void print( HT *global) 
{

    HT *temp;

    int i = 0;

    while( i < MAX) {

        temp = global[i].next;

        printf("key = %-5d %-20s count = %-3d\n", i, global[i].string, global[i].count);

        while( temp) {

            printf("key = %-5d %-20s count = %-3d \n", temp->key, temp -> string, temp->count);
            temp = temp -> next;
        }

        printf("\n");
        i++;
    }
}

/*


   HT *temp = global[key].next;

   printf("key = %d %s count = %d\n", key, global[key].string, global[key].count);

   while( temp) {
   printf("key = %d %s  count = %d \n", temp->key, temp -> string, temp->count);
   temp = temp -> next;
   }
   }*/
