#include <string.h>
#include <stdio.h>
 
char str1[50] = "abcdefgh";
char str2[50] = "abcdefgh";






void * my_memmove1(void * dest,const void *src,size_t count)
{
        char *tmp, *s;

        if (dest <= src) {
                tmp = (char *) dest;
                s = (char *) src;
                while (count--)
                        *tmp++ = *s++;
                }
        else {  
                tmp = (char *) dest + count;
                s = (char *) src + count;
                while (count--)
                        *--tmp = *--s;
                }

        return dest;
}             










void * my_memcpy1(void * dest,const void *src,size_t count)
{
        char *tmp = (char *) dest, *s = (char *) src;

        while (count--)
                *tmp++ = *s++;

        return dest;
}

 
 
int main( void )
{
 
//Use of memmove
//   printf( "Function:\tmemmove with overlap\n" );
   
//   printf( "Orignal :\t%s\n",str1);
   
//   printf( "Source:\t\t%s\n", str1 + 5 );
   
//   printf( "Destination:\t%s\n", str1 + 11 );
   
   my_memmove1( str1 + 2, str1 , 7 );
   
   printf( "Result:\t\t%s\n", str1 );
   
//   printf( "Length:\t\t%d characters\n\n", strlen( str1 ) );
   
 
//Use of memcpy
//   printf( "Function:\tmemcpy with overlap\n" );
   
//   printf( "Orignal :\t%s\n",str2);
   
//   printf( "Source:\t\t%s\n", str2 + 5 );
   
//   printf( "Destination:\t%s\n", str2 + 11 );
   
   my_memcpy1( str2 + 1, str2, 7 );
   
   printf( "Result:\t\t%s\n", str2 );
   
//   printf( "Length:\t\t%d characters\n\n", strlen( str2 ) );
   
   
   return 0;
}
