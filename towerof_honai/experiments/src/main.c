/* program for tower of hanoi by using stacks */


#include"../header/header.h"


int main()
{  
    int i ;
    int n ;           /* for number of disks */
    struct node *source;  /* three stacks */
    struct node *dest;    /* structure is defined in header.h*/
    struct node *temp;
    struct node *first = NULL;

    printf("\nEnter the number of plates in tower1...");
    scanf("%d", &n);

  
    source = (struct node *)malloc(sizeof(struct node)*n);
    source -> next = NULL;
    dest = (struct node *)malloc(sizeof(struct node)*n);
    dest -> next = NULL;
    temp = (struct node *)malloc(sizeof(struct node)*n);
    temp -> next = NULL;
   /* for identifing the stacks*/
    source -> ind = 1;  
    dest -> ind = 2;
    temp -> ind = 3;
    
    /* inserting elements to stcak 1*/
    i = 0;
    while( i < n) {
    source = insert(first);
    first = source;
    i++;
    }

    towerof_hanoi(n, source, dest, temp);
}
