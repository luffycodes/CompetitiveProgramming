#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string.h>
 
using namespace std;
#define MAXN 502
#define INF 2000000000
 
int m,n,x,y,c,t;
class Edge{
  public:
  int from,to,cap,flow,index;
  Edge(int f,int t, int c, int fl,int i){
    from = f,to = t,cap = c; flow = fl;index = i;
  }
};
 
vector<Edge> Graph[MAXN];
 
queue<int> q;
Edge * dad[MAXN];
 
long long GetBlockingFlow(int s, int t){
  for(int i=0;i<MAXN;i++){
    dad[i] = (Edge *)NULL;
  }
 
  q.push(s);
  
  dad[s] = &Graph[0][0]-1;
  
  while(!q.empty()){
    int node = q.front();
    q.pop();
    
    for(int i=0;i<Graph[node].size();i++){
      Edge *e = &Graph[node][i];
      if(e->cap - e->flow>0 && !dad[e->to]){
        dad[e->to] = &Graph[node][i];
        q.push(e->to);
      }
    }
  }
  if(!dad[t])return 0LL;
  
  long long totalflow = 0LL;
  Edge * startc,*start;
  
  for(int i=0;i<Graph[t].size();i++){
    startc = &Graph[t][i];
    start = &Graph[startc->to][startc->index];
    
    int amt = INF;
    for(Edge * ed = start;amt!=0 && ed!=dad[s];ed = dad[ed->from]){
      if(!ed){
        amt =0;
        break;  
      }else{
        amt = min(amt,ed->cap - ed->flow);
      }
    }
    if(amt==0)continue;
    for(Edge * ed = start;amt!=0 && ed!=dad[s];ed = dad[ed->from]){
      ed->flow+=amt;
      Graph[ed->to][ed->index].flow -= amt;
    }
    totalflow += (long long)amt;
  }
  return totalflow;
}
long long GetMaxFlow(int s, int t){
  long long totalflow = 0LL;
  long long flow = 0LL;
  while(flow = GetBlockingFlow(s,t)){
    totalflow+=flow;
  }
  return totalflow;
}
 
bool conn[55][55];
 
int main(){
  int T;
  scanf("%d", &T);
  while(T--){
    memset(conn, false, sizeof(conn));
 
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
      scanf(" (%d,%d)",&x,&y);
      //printf("%d %d\n", x, y);
      conn[x][y] = conn[y][x] = true;      
    }
    int ans = n;
     for(int i = 0;i<n;++i){
      for(int j = i+1;j<n;++j){
         for(int k=0;k<MAXN;k++)
            Graph[k].clear();
          for(int k = 0;k<n;++k){
            x = 2*k;
            y = 2*k+1;
            c = 1;
            // x->y
            Graph[x].push_back(Edge(x,y,c,0,Graph[y].size()));
            if(x==y)Graph[x].back().index ++;
            Graph[y].push_back(Edge(y,x,0,0,Graph[x].size()-1));
            // y->x
            swap(x,y);
            Graph[x].push_back(Edge(x,y,c,0,Graph[y].size()));
            if(x==y)Graph[x].back().index ++;
            Graph[y].push_back(Edge(y,x,0,0,Graph[x].size()-1));
          }
          
          for(int a = 0;a<n;++a) 
            for(int b = 0;b<n;++b){
                  if(!conn[a][b]) 
                    continue;
                  x = 2*a+1;
                  y = 2*b;
                  c = n+1;
                  // x->y
                  Graph[x].push_back(Edge(x,y,c,0,Graph[y].size()));
                  if(x==y)Graph[x].back().index ++;
                  Graph[y].push_back(Edge(y,x,0,0,Graph[x].size()-1));
          }
          
          ans = min(ans,(int)GetMaxFlow(2*i+1,2*j));
      }
    }
    printf("%d\n",ans);
  }
  
  return 0;
} 
