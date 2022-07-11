#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

Node *front=NULL, *rear = NULL;

void enque(int x)
{
    Node *t;
    t = (Node *)malloc(sizeof(Node));
    if(front)
    {
        t->data = x;
        t->next = NULL;
        rear->next = t;
        rear = t;
    }
    else
    {
        t->data = x;
        t->next = NULL;
        front = rear = t;
    }
}

int deque()
{
    Node *p;
    int s;
    if(front)
    {
        p = front;
        front = front->next;
        s = p->data;
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

void BFS(int vtx, int A[][14], int n){
    int visited[12] = {0};
    printf("%d ",vtx-1);
    visited[vtx] = 1;
    enque(vtx);
    while (isEmpty()){
        int u = deque();
        for (int v=1; v<=n; v++){
            if (A[u][v] == 1 && visited[v] == 0){
                printf("%d ",v-1);
                visited[v] = 1;
                enque(v);
            }
        }
    }
}

int main (){
    int n,m;
    scanf("%d %d",&n,&m);
    int A[14][14] ={0};
    for(int i=0;i<m;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        A[x+1][y+1] = 1;
    }
    BFS(1, A, 13);
    printf("\n");
    return 0;
}