/* circularlinkedlist.c */

#include <stdio.h>
#include <stdlib.h>
#include "circularlinkedlist.h"

struct node sentinel = {0, &sentinel, &sentinel};

static link head = &sentinel;

link make_node(unsigned char item)
{
    link p = malloc(sizeof *p);
    p->item = item;
    p->prev = p->next = NULL;

    return p;
}

void free_node(link p)
{
    free(p);
}

link search(unsigned char key)
{
    link p;

    for (p = head->next; p != head; p = p->next)
        if (p->item == key)
            return p;

    return NULL;
}

void insert(link p)
{
    p->next = head->next;
    head->next->prev = p;
    head->next = p;
    p->prev = head;
}

void delete(link p)
{
    p->prev->next = p->next;
    p->next->prev = p->prev;
}

void traverse(void (*visit)(link))
{
    link p;

    for (p = head->next; p != head; p = p->next)
        visit(p);
}

void destroy(void)
{
    link q, p = head->next;
    head->next = head;
    head->prev = head;
    while (p != head) 
    {
        q = p;
        p = p->next;
        free_node(q);
    }
}

void enqueue(link p)
{
    insert(p);
}

link dequeue(void)
{
    if (head->prev == head)
        return NULL;
    else
    {
        link p = head->prev;
        delete(p);
        return p;
    }
}

void print_item(link p)
{
    printf("%d\n", p->item); 
}

int main(void)
{
    link p = make_node(10);
    insert(p);
    p = make_node(5);
    insert(p);
    p = make_node(90);
    insert(p);
    p = search(5);
    delete(p);
    free_node(p);
    traverse(print_item);
    destroy();

    p = make_node(100);
    enqueue(p);
    p = make_node(200);
    enqueue(p);
    p = make_node(250);
    enqueue(p);
    while (p = dequeue()) 
    {
        print_item(p);
        free_node(p);
    }

    return 0;
}
