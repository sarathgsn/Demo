#include<stdio.h>
#include<stdlib.h>
struct node
{
    int ind;
    int ele;
    struct node *next;
};

int g;

void push(struct node *,int);
int pop(struct node *);
void disp(struct node *);
struct node* insert(struct node *);
void towerof_hanoi(int n,struct node *,struct node *,struct node *);

