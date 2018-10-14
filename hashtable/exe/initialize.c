#include "hashing_header.h"

intialize_global_with_zeros(HT *global)
{
    int i;

    for ( i = 0 ; i < MAX; i ++) {

        global[i].count = 0;
     //   strcpy(global[i].string, N) ;
        global[i].next = NULL;
    }

}

























