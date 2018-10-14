#include<stdio.h>

/* basic function declarations for doing 
 * simple hash table without considering collusion*/

int insert(int **);
int hashValue(int );
int search(int);

int main(void) 
{   
    int se;
    int **a;
    int choice;
    int result;

    int i;
    a = (int **) malloc(sizeof(int *) * 10);
    for(i = 0; i < 10; i++)
    {
        a[i] = (int *) malloc(sizeof(int)*2);
        //a[i] = (int *) malloc(sizeof(int));
        //
     }



    while(1)
    {
        printf("\n enter the choice   \n");
        printf("\n 1 for insert  \n");
        printf("\n 2 for search  \n");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1: result = insert(a);
 //                   printf("\n %d  \n", result);
                    break;
            case 2: printf("\n enter the element to be search  \n");  
                    scanf("%d",&se); 
                    result = search(se);
   //                 printf("\n %d  \n", result);
                    printf("\n %d  \n", a[result][0]);
                    printf("\n %d  \n", a[result][1]);

        }
    }
}

int insert(int **a)
{   
     

    int res;
    int num;
    printf("\n enter the number  \n");
    scanf("%d",&num);
    res = hashValue(num);
    *(*( a+res)+0) = res;
    *(*(a + res)+ 1) = num;
//     return res;
}


int hashValue(int num)
{
    int res;
    res = num % 10;
    return res;
}

int search(int key)
{
    int res;
    res = hashValue(key);
    return res;
}
