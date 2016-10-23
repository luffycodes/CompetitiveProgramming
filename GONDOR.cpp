#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <math.h>
 
using namespace std;
#define EPS 0.000001
 
struct node{
	int x;
	double cost;
};
 
bool operator<(const node& a,const node& b)
{
	if(a.cost>b.cost+EPS)
		return true;
	return false;
}
 
#define MAXN 110
 
int graph[MAXN][MAXN];
int place[MAXN][2];
bool vis[MAXN];
int arrow[MAXN];
double sol[MAXN];
int n, m, s, t;
 
double dist(int i, int j)
{
	return sqrt((place[i][0]-place[j][0])*(place[i][0]-place[j][0]) + (place[i][1]-place[j][1])*(place[i][1]-place[j][1]));
}
 
int main()
{
	int i, j, k, T;
	int a, b, c;
	double ans=0.0;
	scanf("%d", &n);
	for(i=1; i<MAXN; i++)
		vis[i]=false;
 
	for(i=1;i<=n;i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		place[i][0]=a;
		place[i][1]=b;
		arrow[i]= c;
		for(j=1; j<=n-1;j++)
			scanf("%d", &graph[i][j]);
	}
	// printf("Input taken\n");
	
	priority_queue<node> q;
	node temp;
	int qx, qy,nx, ny;
	double qcost, ncost;
	int cnt = 0;
 
	q.push((node){1, 0.0});
	while(!q.empty())
	{
		temp = q.top();
		qx = temp.x;
		qcost = temp.cost;
		//printf("qx = %d and cost = %lf\n", qx, qcost);
		q.pop();
 
		if(!vis[qx])
		{
			sol[qx] =qcost;
			vis[qx] = true;
			cnt++;
			if(cnt==n) 
				break;
			for(j=1;j<=n-1 and arrow[qx];j++)
			{
				nx = graph[qx][j];
				/*if(nx==0)
					printf("nx=0 at qx= %d and j of %d\n", qx, j);*/
				if(!vis[nx])
				{
					ncost = qcost + dist(qx, nx);
					q.push((node){nx, ncost});
					arrow[qx]--;
				}
			}
		}
	}
	for(i=1;i<=n;i++)
		printf("%lf\n", sol[i]);
	return 0;
}
