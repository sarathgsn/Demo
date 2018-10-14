/* header of hashing table */
#ifndef __hash__h_
#define __hash__h_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct hashtable {

    int key;
    int count;
    char string[512];
    struct hashtable *next;
}HT;




void *search(char *, HT *);

#endif







