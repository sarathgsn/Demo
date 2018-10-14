
/*using empolyer id generating the key*/

#include "hashing_header.h"

void * search( char *buf , HT *global)
{
    int key;
    int index = 0;
    HT * temp = NULL;
    int value;



    value = generate_ascii( buf );
    key = hash_function( value );


    /*found at starting index of key*/
    if ( strcmp(global[key].string,  buf) == 0  ) {  /* *(g + key).id or (g + key ) -> id */
      //printf("element  found at key %d at an index %d\n", key, index);
        return (global + key);
    }
    else {

        index = 1;
        temp = global[key].next;
        while(temp && (strcmp(buf, temp -> string) != 0) ) {
            temp = temp->next;
            index++;
        }

        if( temp == NULL) {
            //      printf("element not found\n");
            return NULL;
        }
        else{ 
        //  printf("element  found at key %d at an index %d\n", key, index);
            return temp ;



        }
    }
    return NULL;


}








