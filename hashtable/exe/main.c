/*

   program  name: hashing technique implementation 

description : using empolyer id generating the key and insert the id's  in

hashtable for efficient searching and retrieving the data  

*/

#include "hashing_header.h"


int main(int argc, char *argv[])
{
    int index = 0;
    int key;
    int ret1;
    HT *ret;
    FILE *fp;
    char buf[512];
    int option;
    int value;
    char  sbuf[512];

    HT global[MAX];

    if(argc != 2) {
        printf("input format <exe>   <file name> \n");
        exit(0);
    }


    /*for identifying the slot is empty or filled initialize with zeros*/
    (void)intialize_global_with_zeros(global);


    fp = fopen( argv[1] , "r");
    if( fp == NULL) {
        printf("open failed  \n");
        exit(0);
    }

    /*insert in hash table*/
    while(1 ==  fscanf(fp , "%s" , buf)) {

        insert( buf , global);

    }

    printf("\n given file is inserted in hash table format \n");

    while(1) {

     printf("enter the option\n");
     printf("1. search the string \n");
     printf("2. print the hash table \n");

        option = take_input_from_user();                                        



        switch( option ) {                                                      


            case 1:                                                             

                printf("enter the string to search \n");                   
                fgets(sbuf, sizeof(sbuf), stdin);         
                sbuf[strlen(sbuf)-1] = '\0';                
                ret = (HT *)search( sbuf , global ) ;                                   

                if ( ret != NULL ) {                                              
                    printf("element found and its count in file = %d \n", ret->count);                     
                }                                                               
                else {                                                          
                    printf(" element not found \n");                            


                }        


                break;                


            case 2:
                print(global);
                break;

            case 3:
                printf("this is not a valid option\n");
                break;


        }


    }
        return 0;
    }




