#include <stdio.h>
#include <stdlib.h>
#define maxnode 7

typedef struct Node
{
    int  id;
    struct Node *next;
}Node;

typedef struct List
{
    Node *head;
}List;

List *adjlist[maxnode];
int visited[maxnode] = {0};

void addnode(int x, int y)
{
    Node *temp,*dest;
    dest = (Node *)malloc(sizeof(Node));
    dest->id = y;
    dest->next = NULL;
    temp = adjlist[x]->head;
    while(temp->next)
    {
        temp = temp->next;
    }
    temp->next = dest;
}

void dfs(int id)
{
    if(visited[id]==0)
    {
        Node *start = adjlist[id]->head;
        printf("%d ",id);
        visited[id] = 1;
        while(start)
        {
            int x = start->id;
            if(visited[x]==0)
                dfs(x);
            start = start->next;
        }
    }
}

int main()
{
    Node *src;
    for(int i=0;i<maxnode;i++)
    {
        adjlist[i] = (List*)malloc(sizeof(List));
        adjlist[i]->head = NULL;
        src = (Node *)malloc(sizeof(Node));
        src->id = i;
        src->next = NULL;
        adjlist[i]->head = src;
    }
    addnode(0,1);
    addnode(1,3);
    addnode(2,4);
    addnode(3,5);
    addnode(5,2);
    dfs(0);
    return 0;
}