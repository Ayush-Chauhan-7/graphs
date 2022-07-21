#include <stdio.h>
#include <stdlib.h>
#define maxn 10000

typedef struct Node
{
    int id;
    int weight;
    struct Node *next;
}Node;

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

void swap(Node **graph, int i, int j)
{
    Node *temp = graph[i];
    graph[i] = graph[j];
    graph[j] = temp;
}

int size = 0;

void enque(Node **pq, Node *p)
{
    if(size==0)
    {
        pq[size++] = p;
        return;
    }
    pq[size++] = p;
    int i = size-1;
    while(i>0 && p->weight<pq[(i-1)/2]->weight)
    {
        pq[i] = pq[(i-1)/2];
        i = (i-1)/2;
    }
    pq[i] = p;
}

Node *deque(Node **pq)
{
    Node *ret = pq[0];
    size--;
    pq[0] = pq[size];
    int i = 0;
    int j = 2*i + 1;
    while(j<size)
    {
        if(pq[j]->weight > pq[j+1]->weight)
            j++;
        if(pq[i]->weight > pq[j]->weight)
        {
            swap(pq,i,j);
            i = j;
            j = 2*j + 1;
        }
        else
            break;
    }
    return ret;
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
    Node **pq;
    int dist[maxn],prev[maxn];
    dist[0] = 0, prev[0]=-1;
    for(int i=1;i<n;i++)
    {
        dist[i] = 10000;
        prev[i] = -1;
    }
    int vis[maxn] = {0};
    pq = (Node**)malloc(m*sizeof(Node*));
    enque(pq,graph[0]);
    Node *t1,*t2;
    int index, minval, newdist;
    while(size)
    {
        t1 = deque(pq);
        index = t1->id;
        minval = t1->weight;
        vis[index] = 1;
        if(dist[index]<minval)
            continue;
        t2 = graph[index];
        while(t2->next)
        {
            t2 = t2->next;
            if(vis[t2->id])
               continue;
            newdist = dist[index] + t2->weight;
            if(newdist < dist[t2->id])
            {
                prev[t2->id] = index;
                dist[t2->id] = newdist;
                enque(pq,t2);
            }
        }
    }
    int e;
    printf("Find the shortest path for: ");
    scanf("%d",&e);
    int path[maxn],c=0;
    for(int i=e; i>=0; i = prev[i])
    {
        path[c++] = i;
    }
    printf("The shortest path is: ");
    for(int i=c-1;i>=0;i--)
        printf("%d ",path[i]);
    printf("\n");
    return 0;
}