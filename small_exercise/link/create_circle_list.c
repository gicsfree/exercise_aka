/* create_song_list.c */

#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;
struct node 
{
    unsigned char item;
    link prev;
    link next;
};

link make_node(unsigned char item)
{
    link p;

    p = (link)malloc(sizeof *p);
    if (p == NULL)
    {
        printf("memory out\n");
        exit(1);
    }
    p->item = item;
    p->prev = p->next = NULL;

    return p;
}

void free_node(link p)
{
    free(p);
}

link search(unsigned char key, link head)
{
    link p;

    for (p = head->next; p != head; p = p->next)
    {
        if (p->item == key)
        {
            return p;
        }
    }

    return NULL;
}

void insert(link p, link head)
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

void traverse(void (*visit)(link), link head)
{
    link p;

    for (p = head->next; p != head; p = p->next)
    {
        visit(p);
    }
}

void destroy(link head)
{
    link p = head->next;
    link q = head->next;

    head->next = head;
    head->prev = head;

    while (p != head) 
    {
        q = p;
        p = p->next;
        free_node(q);
    }
}

void enqueue(link p, link head)
{
    insert(p, head);
}

link dequeue(link head)
{
    if (head->prev == head)
    {
        return NULL;
    }
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
    struct node sentinel = {0, &sentinel, &sentinel};
    link head = &sentinel;

    link p = make_node(10);
    insert(p, head);
    p = make_node(5);
    insert(p, head);
    p = make_node(90);
    insert(p, head);
    p = search(5, head);
    delete(p);
    free_node(p);
    traverse(print_item, head);
    destroy(head);

    p = make_node(100);
    enqueue(p, head);
    p = make_node(200);
    enqueue(p, head);
    p = make_node(250);
    enqueue(p, head);
    while (p = dequeue(head)) 
    {
        print_item(p);
        free_node(p);
    }

    return 0;
}
