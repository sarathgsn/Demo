#include "../header/header.h"

int main(void) 
{   
    char se[20];
    int choice;
    int result;

    struct hash table[10] = {{0, 0 ,0}} ;

    while(1)
    {
        printf("\n enter the choice   \n");
        printf("\n 1 for insert  \n");
        printf("\n 2 for search  \n");
//        printf("\n 3 for delete  \n");
        printf("\n 4 for count  \n");
//        printf("\n 5 for display for particular key  \n");
        printf("\n   enter--->\t");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:  result = insert(table);
                    // printf("\n key =  %d \n", result);
                     break;
            case 2: printf("\n enter the element to be search  \n");  
                    scanf("%s",se); 
                   // fgets(se, 10, stdin);
                    result = search(se, table);
                    if ( result == 1)
                    printf("\nelement found\n");
                    else
                        printf("\n element not found  \n");
                    break;
            case 3: printf("\n enter the element to be delete \n");
                    //scanf("%d",&se);
                    fgets(se, 10, stdin);
//                    result = delete(table, se);
                    if ( result == 1)
                    printf("\nelement deleted\n");
                    else
                        printf("\n element not found for deleting  \n");
                    break;
                    //printf("\n %d  \n", result);
                    break;
            case 4: printf("\n  enter the key to be count \n");
                    scanf("%s", se);
                  //  fgets(se, 10, stdin);
                    result = count(table, se);
                    printf("\n count = %d  \n", result);
                    break;
            case 5: printf("\n enter the key to be display  \n");
                  //  scanf("%d",&se);
                    fgets(se, 10, stdin);
                   display(table, se);
                    break;
        }
    }
}

















