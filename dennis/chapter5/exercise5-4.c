#include<stdio.h>

#define SIZE 100

int mystrend(char *mptr, char *mstr)
{
    char *ms = NULL;
    char *ss = NULL;

    while( *mptr )
    {
        for ( ms = mptr, ss = mstr;  (*ms == *ss) ; ms++, ss++)
            ;
 //       printf("\n hai  \n");
        if ( ( *ms == '\0' ) || (*ss == '\0') ) {

            return 1;
        }
        mptr++;
    }

    return 0;
}



int main(void) 
{
    char ptr[SIZE] = "GLOBALEDGE";
    char str[SIZE] = "hai";
    int result;


    result =  mystrend(ptr, str);

    printf("\n %d  \n", result);


    return 0;

}
