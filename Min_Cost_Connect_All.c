#include <stdio.h>
#include<stdlib.h>

typedef struct edge
{
    int src;
    int dest;
    int weight;
}edge;

edge edgelist[1000];

void Merge(edge A[1000], int low, int mid, int high){
    int i = low;
    int j = mid+1;
    int k = low;
    int B[high+1],C[high+1],D[high+1];
    while (i <= mid && j <= high){
        if (A[i].weight <= A[j].weight){
            C[k] = A[i].src;
            D[k] = A[i].dest;
            B[k++] = A[i++].weight;
        } else {
            C[k] = A[j].src;
            D[k] = A[j].dest;
            B[k++] = A[j++].weight;
        }
    }
    while (i <= mid){
        C[k] = A[i].src;
        D[k] = A[i].dest;
        B[k++] = A[i++].weight;
    }
    while (j <= high){
        C[k] = A[j].src;
        D[k] = A[j].dest;
        B[k++] = A[j++].weight;
    }
    for (int i=low; i<=high; i++){
        A[i].weight = B[i];
        A[i].src = C[i];
        A[i].dest = D[i];
    }
}
 
void RecursiveMergeSort(edge A[1000], int low, int high){
    if (low < high){
        int mid = low + (high-low)/2;
        RecursiveMergeSort(A, low, mid);
        RecursiveMergeSort(A, mid+1, high);
        Merge(A, low, mid, high);
    }
}

int size=0,numcomponents=0;
int iden[1000],sz[1000];

void CreateUnionFind(int n)
{
    if(n==0)
        return;
    size = numcomponents = n;
    for(int i=0;i<size;i++)
    {
        iden[i] = i;
        sz[i] = 1;
    }
}

int Find(int p)
{
    int root=p;
    while(iden[root]!=root)
    {
        root = iden[root];
    }
    int temp;
    while(p!=root)
    {
        temp = iden[p];
        iden[p] = root;
        p = temp;
    }
    return root;
}

void Union(int p, int q)
{
    int root1 = Find(p);
    int root2 = Find(q);
    if(root1==root2)
        return;
    if(sz[root1]>sz[root2])
    {
        sz[root1]+=sz[root2];
        iden[root2] = root1;
        sz[root2] = 0;
    }
    else
    {
        sz[root2]+=sz[root1];
        iden[root1] = root2;
        sz[root1] = 0;
    }
    numcomponents--;
}

int distance(int x1,int x2,int y1, int y2)
{
    return abs(x1-x2) + abs(y1-y2);
}

int main()
{
    int n;
    scanf("%d",&n);
    int counter = 0;
    int points[n][2];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&points[i][0]);
        scanf("%d",&points[i][1]);
    }
    int dum;
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            dum = distance(points[i][0],points[j][0],points[i][1],points[j][1]);
            edgelist[counter].src = i;
            edgelist[counter].dest = j;
            edgelist[counter++].weight = dum;
        }
    }
    RecursiveMergeSort(edgelist,0,counter-1);
    CreateUnionFind(n);
    int i=0,j=0;
    edge MST[n-1];
    while(numcomponents>1 && j<counter && i<n-1)
    {
        if(Find(edgelist[j].src)!=Find(edgelist[j].dest))
        {
            Union(edgelist[j].src, edgelist[j].dest);
            MST[i].src = edgelist[j].src;
            MST[i].dest = edgelist[j].dest;
            MST[i++].weight = edgelist[j].weight;
        }
        j++;
    }
    if(i==n-1)
    {
        int sum = 0;
        for(int i=0;i<n-1;i++)
            sum += MST[i].weight;
        printf("%d\n",sum);
    }
    else
    {
        printf("-1\n");
    }
    return 0;
}