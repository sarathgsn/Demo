#include"../header/header.h"


int insert(struct hash *node)
{   


    int res;
    int num;

    printf("\n enter the number  \n");
    scanf("%d",&num);


    res = hashValue(num);




   if ( node[res] .key == 0 )
   {
        node[res] . key = res;
        node[res] . data  = num;
        node[res] . next = NULL;
        return res;

    } else if ( node[res].data == 0 && node[res].next != NULL)
    {
        struct node *ttr = (struct node *) node[res].next;
              node[res].key = res;
              node[res].data = num;
              node[res].next = (struct hash *)ttr;
              return res;
    }
  
  
  
   else if( node[res].next == NULL)
   {
       struct node *temp = (struct node *)malloc(sizeof(struct node));
       temp -> data = num;
       temp -> link = NULL;
       node[res].next = (struct hash *)temp;
       return res;
   }else
   {
       struct node *ptr = (struct node *)node[res].next;
       struct node *p = ptr;
       while ( p->link != NULL)
       {
           p = p->link;
       }
       struct node *str = (struct node *)malloc(sizeof(struct node));
       str -> data = num;
       str -> link = NULL;
       p -> link = str;
       str = p;
       p = ptr;
       return res;
   }
}

