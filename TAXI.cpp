#include <stdio.h>
#include <algorithm>
#include <queue>
 
using namespace std;
 
#define MAX 701
#define NIL 0
#define INF (1<<28)
 
vector< int > G[MAX];
int n, m, match[MAX], dist[MAX];
int per[410][2], car[210][2];
// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// G = NIL[0] âª G1[G[1---n]] âª G2[G[n+1---n+m]]
 
bool bfs() {
    int i, u, v, len;
    queue< int > Q;
    for(i=1; i<=n; i++) {	//all the free vertices (i.e. are not a part of the matching) in the left side, are added to the queue
        if(match[i]==NIL) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[NIL] = INF;
    while(!Q.empty()) {
        u = Q.front(); 
        Q.pop();
        if(u!=NIL) {
            len = G[u].size();
            for(i=0; i<len; i++) {
                v = G[u][i];
                if(dist[match[v]]==INF) {	// if the distance of predecessor of this node v (in right hand side) from the source node is inf, that node is not in the matching, so add it
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}
 
bool dfs(int u) {
    int i, v, len;
    if(u!=NIL) {
        len = G[u].size();
        for(i=0; i<len; i++) {
            v = G[u][i];
            if(dist[match[v]]==dist[u]+1) {
                if(dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}
 
int hopcroft_karp() {
    int matching = 0, i;
    // match[] is made NIL for all vertex in G
    for(int j=0; j<MAX;j++)
    	match[j]=NIL;
    
    while(bfs())
        for(i=1; i<=n; i++)
            if(match[i]==NIL && dfs(i))
                matching++;
    return matching;
    //maximum number of matching returned here
}
 
int s, c;
 
bool dist1(int cno, int pno)
{
    int d = abs(car[cno][0]-per[pno][0])+abs(car[cno][1]-per[pno][1]);
    d = d*200;
    if(d>=0 and d<=s*c)
        return true;
    return false;
}
 
int main()
{
	int A, B, P, T, k, i, j;
 
	scanf("%d", &T);
	while(T--)
	{
        scanf("%d %d %d %d", &n, &m, &s, &c);
		for(i=0; i<MAX;i++)
			G[i].clear();
        
        for(i=0; i<n; i++)
            scanf("%d %d", &per[i][0], &per[i][1]);
        for(i=0; i<m; i++)
        {
            scanf("%d %d", &car[i][0], &car[i][1]);
            for(j=0; j<n; j++)
            {
                if(dist1(i, j))
                {
                    G[j+1].push_back(n+i+1);
                    G[n+i+1].push_back(j+1);
                }
            }
        }
		printf("%d\n", hopcroft_karp());
	}
	return 0;
}
