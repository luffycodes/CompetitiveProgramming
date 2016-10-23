#include <stdio.h>
#include <queue>
#include <vector>
#include <assert.h>
 
using namespace std;
 
#define MAXN 510
#define MAXM 10010
 
#define INF 1000000000
 
#define DEBUGMODE 0
#define DEBUG(args ...)  if (DEBUGMODE) fprintf(stderr, args)
 
class Edge{
    public:
    int from, to, wt, id;
    Edge(){}
    Edge(int f, int t, int w, int i){
        from = f, to = t;
        wt = w;
        id = i;
    }
};
 
typedef pair<int, pair<int,Edge> > QueElem;
typedef pair<int,int> DijElem;
 
class Compare{
    public:
    bool operator() (const QueElem& a, const QueElem& b) const {
        if (a.first==b.first)
            return a.second.first>b.second.first;
        return a.first>b.first;
    }
};
 
class Compare2{
    public:
    bool operator() (const DijElem& a, const DijElem& b) const {
        if (a.first==b.first)
            return a.second>b.second;
        return a.first>b.first;
    }
};
 
vector<Edge> graph[MAXN], revSPGraph[MAXN];
bool isMarked[MAXM], vis[MAXM];
int dist[MAXN];
priority_queue<QueElem, vector<QueElem>, Compare> q;     // (wt, (v,edge))
priority_queue<DijElem, vector<DijElem>, Compare2> q2;   // (wt, v)
 
void CreateRevSPGraph(int N, int M, int S, int D){
    DEBUG("CreateRevSPGraph(%d,%d,%d,%d)\n", N, M, S, D);
    int i, j, v, d;
    QueElem p;
    Edge e;
    
    while (not q.empty()) q.pop();
    for (i=0; i<N; i++){
        dist[i] = INF;
        revSPGraph[i].clear();
    }
    for (i=0; i<M; i++) vis[i] = false;
    dist[S] = 0;
    for (i=0; i<graph[S].size(); i++){
        e = graph[S][i];
        q.push(make_pair(e.wt, make_pair(e.to,e)));
    }
    
    while (not q.empty()){
        p = q.top();
        q.pop();
        d = p.first, v = p.second.first, e = p.second.second;
        assert(v==e.to);
        if (d <= dist[v]){
            dist[v] = d;
            revSPGraph[v].push_back(Edge(v, e.from, e.wt, e.id));
        }
        for (i=0; i<graph[v].size(); i++){
            e = graph[v][i];
            if (vis[e.id]) continue;
            vis[e.id] = true;
            q.push(make_pair(dist[v]+e.wt, make_pair(e.to,e)));
        }
    }
}
 
void Dfs(int v){
    for (int i=0; i<revSPGraph[v].size(); i++){
        isMarked[revSPGraph[v][i].id] = true;
        Dfs(revSPGraph[v][i].to);
    }
}
 
void MarkSPEdges(int N, int M, int S, int D){
    DEBUG("MarkSPEdges(%d,%d,%d,%d)\n", N, M, S, D);
    for (int i=0; i<M; i++)
        isMarked[i] = false;
    Dfs(D);
}
 
void Dijkstra(int N, int M, int S, int D){
    DEBUG("Dijkstra(%d,%d,%d,%d)\n", N, M, S, D);
    DijElem p;
    int i, v, d;
    Edge e;
    
    for (i=0; i<N; i++) dist[i] = INF;
    for (i=0; i<M; i++) vis[i] = false;
    dist[S] = 0;
    while (not q2.empty()) q2.pop();
    q2.push(make_pair(0,S));
    
    while (not q2.empty()){
        p = q2.top();
        q2.pop();
        v = p.second, d = p.first;
        if (d < dist[v]) dist[v] = d;
        if (v==D) return;
        for (i=0; i<graph[v].size(); i++){
            e = graph[v][i];
            if (isMarked[e.id] or vis[e.id]) continue;
            vis[e.id] = true;
            q2.push(make_pair(dist[v]+e.wt, e.to));
        }
    }
}
 
int Solve(int N, int M, int S, int D){
    CreateRevSPGraph(N,M,S,D);
    MarkSPEdges(N,M,S,D);
    Dijkstra(N,M,S,D);
    if (dist[D] < INF)
        return dist[D];
    return -1;
}
 
int main(){
    int N, M, S, D, U, V, P;
    int i, j, id, ans;
    
    scanf("%d %d", &N, &M);
    while (N>0){
        id = 0;
        for (i=0; i<N; i++)
            graph[i].clear();
        scanf("%d %d", &S, &D);
        for (i=0; i<M; i++){
            scanf("%d %d %d", &U, &V, &P);
            graph[U].push_back(Edge(U,V,P,id++));
        }
        printf("%d\n", Solve(N,M,S,D));
        scanf("%d %d", &N, &M);
    }
    
    return 0;
}
