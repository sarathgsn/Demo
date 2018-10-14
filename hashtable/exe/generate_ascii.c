#include "hashing_header.h"

int generate_ascii(char *buf) 
{
    int  ascii_count = 0;
    int i = 0;
    int  odd_letters_count = 0;

    while(*(buf + i) != '\0') {

        ascii_count += (*buf);

        if( (i % 2) == 1) {
            odd_letters_count += (*buf);
        }

        i++;
    }


    /* adding some extra value for efficient ascii*/
    return ascii_count + odd_letters_count;
}


