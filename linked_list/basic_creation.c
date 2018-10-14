#include<stdio.h>
#include<stdlib.h>



struct node {

    int data;
    struct node *next;
};

struct node* create(struct node*, int);
struct node* insert(struct node*, int);
void display(struct node*);


int main(void) 
{
    int option , data;

    struct node *head = NULL;
    
//    head = (struct node *)malloc(sizeof(struct node));
while(1) 
{ 
      
    printf("\n 1 for inseret  \n");

    printf("\n 2 for display  \n");

    printf("\n enter   \n");

    scanf("%d", &option);

    switch(option)
    {

        case 1 : printf("\n enter the element  \n");
                 scanf("%d", &data);

               head =  insert(head, data);
                 break;

        case 2 :
                 display(head);
                 break;
    }
}
    return 0;
}


struct node* insert(struct node *head, int data)
{
    
    struct node *temp = NULL;
     temp = (struct node *)malloc(sizeof(struct node ));


    if ( head == NULL)
    {
       head = create(head, data);
        return head;
    }
    else {
        temp = head;
        while ( temp -> next  != NULL)
                {
                    temp = temp -> next;
                }
               temp = create(temp, data);
               return head;
    }
}

struct node * create(struct node *head, int data)
{
    struct node *temp = NULL;
    temp = (struct node *)malloc(sizeof(struct node));
    

    temp -> data = data;
    temp -> next = NULL;
//    head = temp;
    return temp;
} 

void display(struct node *head)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = head;
    while( temp != NULL)
    {
        printf("\n data is = %d  \n",temp -> data);
        temp =temp -> next;
    }
}
    
