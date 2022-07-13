#include <stdio.h>
#include <stdlib.h>
#define maxnode 201
 
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
    int n,m;
    scanf("%d",&n);
    scanf("%d",&m);
    for(int i=0;i<n;i++)
    {
        adjlist[i] = (List*)malloc(sizeof(List));
        adjlist[i]->head = NULL;
        src = (Node *)malloc(sizeof(Node));
        src->id = i;
        src->next = NULL;
        adjlist[i]->head = src;
    }
    int x,y;
    while(m--)
    {
        scanf("%d",&x);
        scanf("%d",&y);
        addnode(x-1,y-1);
        addnode(y-1,x-1);
    }
    int count=0;
        for(int i=0; i<n; i++) {
            if(!visited[i]) {
                count++;
                dfs(i);
            }
        }
    printf("%d\n",count);
    return 0;
}