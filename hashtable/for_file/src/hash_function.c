#include"../header/header.h"

int hashValue(char *string)
{ 
//   printf("\n in hashfun  \n"); 
    int count = 0;
    int total = 0;
    int i, res; 
    count = strlen(string);
for( i = 0; i < count; i++)
{
    total += *(string + i);
}


res = total % 10;

return res;
//printf("\n total is =%d  \n", total);
}
