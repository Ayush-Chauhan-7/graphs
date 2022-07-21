#include <stdio.h>
#include <stdlib.h>
#define maxn 10000

typedef struct Node
{
    int id;
    int weight;
    struct Node *next;
}Node;

int visited[maxn] = {0};

void addnode(Node **graph, int x, int y, int z)
{
    Node *dest, *temp;
    dest = (Node*)malloc(sizeof(Node));
    dest->id = y;
    dest->weight = z;
    temp = graph[x];
    while(temp->next)
        temp = temp->next;
    temp->next = dest;
}

void dfs(Node **graph, int id)
{
    if(visited[id]==0)
    {
        Node *start = graph[id];
        printf("%d ",id);
        visited[id] = 1;
        while(start)
        {
            int x = start->id;
            if(visited[x]==0)
                dfs(graph, x);
            start = start->next;
        }
    }
}

int main()
{
    int n,m;
    scanf("%d",&n);
    scanf("%d",&m);
    Node** graph = (Node**)malloc(n*sizeof(Node*));
    Node *t;
    for(int i=0;i<n;i++)
    {
        t = (Node*)malloc(sizeof(Node));
        t->id = i;
        t->weight = 0;
        t->next = NULL;
        graph[i] = t;
    }
    int x,y,z;
    for(int i=0;i<m;i++)
    {
        scanf("%d",&x);
        scanf("%d",&y);
        scanf("%d",&z);
        addnode(graph,x,y,z);
    }
    dfs(graph,0);
    printf("\n");
    return 0;
}