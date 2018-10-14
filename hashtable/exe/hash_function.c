/* hash_function implementation */

#include "hashing_header.h"



int hash_function( int id )
{
    int key;

    key = ( id ) % MAX;

    return key;
}



