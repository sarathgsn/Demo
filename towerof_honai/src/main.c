#include"../header/header_towersof_honai.h"

int stack2_size = 4;  /* global variables for stack1*/
int stack2[4];
int top_stack2 = -1;

int stack1_size = 4;   /* for stack2 */
int stack1[4];
int top_stack1 = -1;


int stack3_size = 4;   /* stack3 */
int stack3[4];
int top_stack3 = -1;

int main(void)
{
    int result;
    int choice;
    int element;
    while(1) 
    {
        printf("\n enter the choice \n");
        printf("\n 1 for push \n");
        printf("\n 2 for towerof_honai \n");
       
    
        scanf("%d",&choice);


        switch(choice)
        {

            case  1 : printf("\n enter the element \n");
                      scanf("%d", &element);
                      push_stack1(element);
                      break;
            case 2 :  towerof_honai();
                      break;
        }
    }
}




 
