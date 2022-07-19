#include <stdio.h>
#include <stdlib.h>
#define maxnode 100000
#define ll long long int
 
typedef struct Node
{
    int  id;
    int weight;
    struct Node *next;
}Node;
 
typedef struct List
{
    Node *head;
}List;

typedef struct Priority_Queue
{
    int id;
    int weight;
}PQ;

List *adjlist[maxnode];
int visited[maxnode] = {0};

void addnode(int x, int y,int z)
{
    Node *temp,*dest;
    dest = (Node *)malloc(sizeof(Node));
    dest->id = y;
    dest->weight = z;
    dest->next = NULL;
    temp = adjlist[x]->head;
    while(temp->next)
    {
        temp = temp->next;
    }
    temp->next = dest;
}

Node pque[10000];
int size=0;

void swap(Node *x, Node *y)
{
    Node temp = *x;
    *x = *y;
    *y = temp;
}

void enque(Node *p)
{
    if(size==0)
    {
        pque[size].id = p->id;
        pque[size].next = p->next;
        pque[size++].weight = p->weight;
        return;
    }
    pque[size].id = p->id;
    pque[size].next = p->next;
    pque[size++].weight = p->weight;
    int i = size-1;
    while(i>0 && p->weight<pque[(i-1)/2].weight)
    {
        pque[i] = pque[(i-1)/2];
        i = (i-1)/2;
    }
    pque[i].weight = p->weight;
    pque[i].id = p->id;
    pque[i].next = p->next;
}

Node* deque()
{
    Node *ret;
    ret = (Node*)malloc(sizeof(Node));
    ret->id = pque[0].id;
    ret->weight = pque[0].weight;
    ret->next = pque[0].next;
    size--;
    pque[0] = pque[size];
    int i= 0; 
    int j= 2*i + 1;
    while(j<size)
    {
        if(pque[j].weight>pque[j+1].weight)
            j = j+1;
        if(pque[i].weight>pque[j].weight)
        {
            Node tt = pque[i];
            pque[i] = pque[j];
            pque[j] = tt;
            i = j;
            j = 2*j+1;
        }
        else
            break;
    }
    return ret;
}

void dfs(int id)
{
    if(visited[id]==0)
    {
        Node *start = adjlist[id]->head;
        visited[id] = 1;
        printf("%d ",id);
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
    int n;
    ll m;
    scanf("%d",&n);
    scanf("%lld",&m);
    for(int i=0;i<n;i++)
    {
        adjlist[i] = (List*)malloc(sizeof(List));
        adjlist[i]->head = NULL;
        src = (Node *)malloc(sizeof(Node));
        src->id = i;
        src->weight = 0;
        src->next = NULL;
        adjlist[i]->head = src;
    }
    int x,y,z;
    while(m--)
    {
        scanf("%d",&x);
        scanf("%d",&y);
        scanf("%d",&z);
        addnode(x,y,z);
    }
    int visited[maxnode] = {0};
    int distance[maxnode] = {1000};
    distance[0] = 0;
    enque(adjlist[0]->head->next);
    Node *t,*temp;
    int dum, newdist, index;

    dfs(0);
    printf("\n");

    while(size>0)
    {
        t = deque();
        printf("%d %d\n",t->id,t->weight);
        index = t->id;
        visited[index] = 1;
        temp = adjlist[index]->head;
        //if(distance[index]<t->weight) continue;
        while(temp->next)
        {
            temp = temp->next;
            dum = temp->id;
            printf("%d %d\n",temp->id,temp->weight);
            if(visited[dum])
                continue;
            newdist = distance[index] + temp->weight;
            if(newdist < distance[dum])
            {
                distance[dum] = newdist;
                enque(temp);
            }
        }
    }
    for(int i=0;i<n;i++)
        printf("%d ",distance[i]);
    printf("\n");
    return 0;
}

