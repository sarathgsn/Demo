#include "hashing_header.h"
int take_input_from_user()
{

    char arr[10];
    int value;

    fgets( arr, sizeof( arr ), stdin);
    value = atoi( arr );

    return value;

}










