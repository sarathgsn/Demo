#include"../header/header.h"
void push(struct node *head, int x)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp -> ele = x;
    temp -> next = head -> next;
    head -> next = temp;
}

