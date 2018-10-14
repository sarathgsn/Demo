#include"../header/header.h"
void disp(struct node *head)
{
    struct node *p;
    p=head->next;
    printf("\nThe ele are...");
    while(p!=NULL)
    {
        printf("%d\t",p->ele);
        p=p->next;
    }
}
