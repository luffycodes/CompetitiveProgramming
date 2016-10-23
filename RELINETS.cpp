#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
#define MAXN 17
#define INF 1000000000
 
struct Edge{
	int u;
	int v;
	int c;
};
 
vector<Edge> edges;
int N, M;
int deg[MAXN];
 
//for union find
int parent[MAXN];
int size[MAXN];
int comps;
 
int getparent(int a){
	if(parent[a]==a)
		return a;
	return getparent(parent[a]);
}
 
void merge(int a, int b){
	int pa = getparent(a);
	int pb = getparent(b);
	if(pa!=pb){
		comps--;
		if(size[pa]>size[pb]){
			parent[pb] = pa;
			size[pa]+=size[pb];
		}else{
			parent[pa] = pb;
			size[pb]+= size[pa];
		}
	}
}
 
int solve(){
	int ans = INF;
	int cost;
	int a, b;
 
	for(int bit=0; bit < (1<<M); bit++){
		cost = 0;
		memset(deg, 0, sizeof(deg));
		
		for(int i=0;i<N; i++){
			parent[i]=i;
			size[i]=i;
		}
		comps = N;
		int i = bit;
 
		for(int j = 0; j<M;j++){
			if(i&1){
				a = edges[j].u;
				b = edges[j].v;
 
				merge(a, b);
				deg[a]++;
				deg[b]++;
				cost += edges[j].c;
			}
			i = i>>1;
		}
 
		bool biconn = true;
		for(int j=0;j<N;j++)
			if(deg[j]<2 or (deg[j]&1))
				biconn = false;
 
		if(comps==1 and biconn)
			ans = min(ans, cost);
	}
	return ans;
}
 
int main(){
	int tests=1;
	int i, j, k;
	int u, v, x, y, c, cost;
	while(1){
		scanf("%d %d", &N, &M);
		if(N==0 and M==0)
			break;
		edges.clear();
		int ans = INF;
 
		for(i=0;i<M;i++){
			scanf("%d %d %d", &u, &v, &c);
			edges.push_back((Edge){u-1, v-1, c});
		}
		
		ans = solve();
 
		if(ans!=INF)
			printf("The minimal cost for test case %d is %d.\n", tests, ans);
		else
			printf("There is no reliable net possible for test case %d.\n", tests);
		tests++;
	}
	return 0;
}
