#include"../header/header.h"
int pop(struct node *head)
{
    if (head->next == NULL)
    {
        return;
    }
    struct node *p;
    int t = 0;
    p = head -> next;
    t = p -> ele;
    head -> next = head -> next -> next;
    free(p);
    return t;
}

