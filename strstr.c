#include<stdio.h>

char* mystrstr(char*,  char*);
int main(void) 
{
    char mstr[50] = "hello world global edge world  hai world  ";
    char sstr[10] = "world";
    char *ptr;

    ptr = mystrstr(mstr, sstr);

    if ( ptr == NULL)
    {
        printf("\n string not found  \n");
    } else {
        printf("\n  string is =  %s \n", ptr);


    }

        return 0;
}
char* mystrstr(char *mstr, char *sstr)
{
    char *mt;
    char *st;


    while( *mstr)
    {
        for ( mt = mstr, st = sstr; (*mt == *st) && ( *mt != '\0'); mt++, st++) {}
        if ( *st == '\0')
        {
            return mstr;
        }
        mstr++;
    }
    return NULL;
}

