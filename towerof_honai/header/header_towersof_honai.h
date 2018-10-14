#ifndef tower
#define tower
#include<stdio.h>
extern int stack2_size ;  /* global variables for stack1*/
extern int stack2[4];
extern int top_stack2;

extern int stack1_size;   /* for stack2 */
extern int stack1[4];
extern int top_stack1;


extern int stack3_size;   /* stack3 */
extern int stack3[4];
extern int top_stack3 ;


int push_stack1(int);   /* stack operations for stack1 */
int pop_stack1();
int display_stack1();




int push_stack2(int);   /* for stack2 */
int pop_stack2();
int display_stack2();

int push_stack3(int);  /* for stack3 */
int pop_stack3();
int display_stack3();
 

/* function declaration for towers_of_honai */

int towerof_honai();
#endif
