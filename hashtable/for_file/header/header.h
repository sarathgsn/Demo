#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct hash
{
    int key;
    char data[10];
    struct hash *next;
};


struct node 
{
    char data[10];
    struct node *link;
};

void display(struct hash *, int);
int count(struct hash *, char *);
int delete(struct hash *, int);
struct hash*  create_node(struct hash * , int);
int insert(struct hash *);
int hashValue(char * );
int search(char *, struct hash *);

