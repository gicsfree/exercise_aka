/* circularlinkedlist.h */

#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

typedef struct node *link;
struct node {
    unsigned char item;
    link prev, next;
};

link make_node(unsigned char item);
void free_node(link p);
link search(unsigned char key);
void insert(link p);
void delete(link p);
void traverse(void (*visit)(link));
void destroy(void);
void enqueue(link p);
link dequeue(void);

#endif
