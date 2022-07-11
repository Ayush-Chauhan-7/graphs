#include <stdio.h>
#include <stdlib.h>

int s[2];

typedef struct Node
{
    int x;
    int y;
    struct Node *next;
}Node;

Node *front=NULL, *rear = NULL;

void enque(int x,int y)
{
    Node *t;
    t = (Node *)malloc(sizeof(Node));
    if(front)
    {
        t->x = x;
        t->y = y;
        t->next = NULL;
        rear->next = t;
        rear = t;
    }
    else
    {
        t->x = x;
        t->y = y;
        t->next = NULL;
        front = rear = t;
    }
}

int *deque()
{
    Node *p;
    if(front)
    {
        p = front;
        front = front->next;
        s[0] = p->x;
        s[1] = p->y;
        free(p);
    } 
    return s;
}

int isEmpty()
{
    if(front)
        return 1;
    else 
        return 0;
}

int main()
{
    enque(5,7);
    enque(8,9);
    int *n = deque();
    printf("%d %d",n[0],n[1]);
}