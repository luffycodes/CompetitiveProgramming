#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
 
using namespace std;
 
struct node{
	int x;
	long long cost;
};
 
bool operator<(const node& a,const node& b)
{
	if(a.cost>b.cost)
		return true;
	return false;
}
 
#define MAXN 1000010
#define INF 100000000000000LL
 
vector< pair<int, int> > graph[MAXN];
vector< pair<int, int> > graph2[MAXN];
long long paths[MAXN];
bool vis[MAXN];
int n, m, s, t;
 
int main()
{
	int i, j, k, T, cnt;
	int a, b, c;
	long long ans;
	scanf("%d", &T);
	while(T--)
	{
		for(i=0; i<MAXN; i++)
			graph[i].clear();
		for(i=0; i<MAXN; i++)
			graph2[i].clear();
		for(i=0; i<MAXN; i++)
			vis[i]=false;
		for(i=0; i<MAXN; i++)
			paths[i]=INF;
		cnt = 0;
		ans = 0LL;
		scanf("%d %d", &n, &m);
		for(i=0;i<m;i++)
		{
			scanf("%d %d %d", &a, &b, &c);
			graph[a].push_back(make_pair(b, c));
			graph2[b].push_back(make_pair(a, c));
		}
		// printf("Input taken\n");
		
		priority_queue<node> q;
		node temp;
		int qx, qy, qcost, nx, ny, ncost;
 
		q.push((node){1, 0LL});
		while(!q.empty())
		{
			temp = q.top();
			qx = temp.x;
			qcost = temp.cost;
			//printf("%d %lld\n", qx, qcost);
			q.pop();
			vis[qx]= true;
 
			if(paths[qx]==INF)
			{
				ans = ans + qcost;
				paths[qx] = qcost;
				cnt++;
				if(cnt==n) break;
			}
 
			for(j=0;j<graph[qx].size();j++)
			{
				nx = graph[qx][j].first;
				ncost = qcost + graph[qx][j].second;
				if(!vis[nx])
					q.push((node){nx, ncost});
			}
		}
		//now returning
		while(!q.empty())
			q.pop();
		for(i=0; i<MAXN; i++)
			vis[i]=false;
		for(i=0; i<MAXN; i++)
			paths[i]=INF;
		cnt = 0;
 
		q.push((node){1, 0LL});
		while(!q.empty())
		{
			temp = q.top();
			qx = temp.x;
			qcost = temp.cost;
			//printf("at %d and with cost %lld\n", qx, qcost);
			q.pop();
			vis[qx]= true;
 
			if(paths[qx]==INF)
			{
				ans = ans + qcost;
				paths[qx] = qcost;
				cnt++;
				if(cnt==n) break;
			}
 
			for(j=0;j<graph2[qx].size();j++)
			{
				nx = graph2[qx][j].first;
				ncost = qcost + graph2[qx][j].second;
				if(!vis[nx])
					q.push((node){nx, ncost});
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
