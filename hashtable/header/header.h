#include<stdio.h>
#include<stdlib.h>

struct hash
{
    int key;
    int data;
    struct hash *next;
};


struct node 
{
    int data;
    struct node *link;
};

void display(struct hash *, int);
int count(struct hash *, int);
int delete(struct hash *, int);
struct hash*  create_node(struct hash * , int);
int insert(struct hash *);
int hashValue(int );
int search(int, struct hash *);

