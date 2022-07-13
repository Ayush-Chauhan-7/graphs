#include<stdio.h>
#include<stdlib.h>
 
static int visited[200] = {0}; 
 
void DFS(int u, int A[][201], int n){
    if (visited[u] == 0){
        visited[u] = 1;
        for (int v=1; v<=n; v++){
            if (A[u][v] == 1 && visited[v] == 0){
                DFS(v, A, n);
            }
        }
    }
}
 
int main (){
 
    int n,m;
    scanf("%d %d",&n,&m);
    int A[201][201] ={0};
    for(int i=0;i<m;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        A[x+1][y+1] = 1;
        A[y+1][x+1] = 1;
    }
    int count = 0;
    for(int i=1;i<=n;i++)
    {
        if(visited[i]==0)
        {
            count++;
            DFS(i,A,n);
        }
    }
    printf("%d\n",count);
    return 0;
}