/* function for inserting elements to stack */


#include"../header/header.h"

struct node* insert(struct node *first)
{   
    struct node *ptr;
    int element;
    printf("\n enter the element \n");
    scanf("%d",&element);


    /* creating a new node */

    ptr = (struct node *)malloc(sizeof(struct node));
    ptr -> ind = 1;
    ptr -> ele = element;
    ptr -> next = NULL;
   
    /* if there is no elements in stack */
   if (first == NULL)
   {
       first = ptr;
       return first;
   } else {
       struct node *temp = first; 

       while( temp->next != NULL)  /* more than one value in stack*/
       {
          temp = temp -> next;
       }
       temp -> next = ptr;
       ptr = first;
       return first;
   }
}
