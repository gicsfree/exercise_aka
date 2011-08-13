/* linkedlist.c */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

static link head = NULL;

link make_node(unsigned char item)
{
    link p = malloc(sizeof *p);
    p->item = item;
    p->next = NULL;

    return p;
}

void free_node(link p)
{
    free(p);
}

link search(unsigned char key)
{
    link p;

    for (p = head; p; p = p->next)
        if (p->item == key)
        return p;

    return NULL;
}

void insert(link p)
{
    p->next = head;
    head = p;
}

void delete(link p)
{
    link pre;

    if (p == head) 
    {
        head = p->next;
        return;
    }
    for (pre = head; pre; pre = pre->next)
        if (pre->next == p) 
        {
            pre->next = p->next;
            return;
        }
}

void traverse(void (*visit)(link))
{
    link p;

    for (p = head; p; p = p->next)
        visit(p);
}

void destroy(void)
{
    link q, p = head;

    head = NULL;
    while (p) 
    {
        q = p;
        p = p->next;
        free_node(q);
    }
}

void push(link p)
{
    insert(p);
}

link pop(void)
{
    if (head == NULL)
        return NULL;
    else {
        link p = head;
        head = head->next;
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
    push(p);
    p = make_node(200);
    push(p);
    p = make_node(250);
    push(p);
    while (p = pop()) 
    {
        print_item(p);
        free_node(p);
    }

    return 0;
}
