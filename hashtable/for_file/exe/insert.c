#include"../header/header.h"


int insert(struct hash *node)
{   

    int no_of_char = 0;
    int res;
    int result;
    char num[10];
    FILE *fp;

    fp = fopen("insert.c", "r");
    
/*    if( fp == NULL)
    {
        printf("\n error   \n");
    }*/
while (  fscanf( fp, "%s",num) != EOF)
{
   printf("\n %s  \n", num);
//    printf("\n enter the number  \n");
//    scanf("%d",&num);



    res = hashValue(num);




   if ( node[res] .key == 0 )
   {
        node[res] . key = res;
      strcpy(node[res] . data , num);
        node[res] . next = NULL;
        printf("\n res = %d  \n", res);
//        return res;
  
   } else if ( node[res].data == NULL && node[res].next != NULL)
    {
        struct node *ttr = (struct node *) node[res].next;
             
     
              node[res].key = res;
      strcpy(node[res] . data , num);
              //node[res].data = num;
              node[res].next = (struct hash *)ttr;
        printf("\n res = %d  \n", res);
  //            return res;
    }
  
  
  
   else if( node[res].next == NULL)
   {
       struct node *temp = (struct node *)malloc(sizeof(struct node));
      strcpy( temp -> data, num);
       temp -> link = NULL;
       node[res].next = (struct hash *)temp;
        printf("\n res = %d  \n", res);
    //   return res;
   }else
   {
       struct node *ptr = (struct node *)node[res].next;
       struct node *p = ptr;
       while ( p->link != NULL)
       {
           p = p->link;
       }
       struct node *str = (struct node *)malloc(sizeof(struct node));
      strcpy( str -> data, num);
       str -> link = NULL;
       p -> link = str;
       str = p;
       p = ptr;
        printf("\n res = %d  \n", res);
      // return res;
   }
   fseek(fp, 1, SEEK_CUR);
}
}
