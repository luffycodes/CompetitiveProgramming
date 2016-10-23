#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <assert.h>
 
using namespace std;
 
int max(int a, int b)
{
	if(a>b)
		return a;
	return b;
}
 
int min(int a, int b)
{
	if(a<b)
		return a;
	return b;
}
 
#define MAX 110
#define INF 1000000
 
int ar[MAX][MAX];
bool vis[MAX][MAX];
int dx[]={-1, 0, 0, 1};
int dy[]={0, -1, 1, 0};
int r, c, t;
 
bool valid(int p, int q)
{
	if(p>=0 and p<r and q>=0 and q<c and !vis[p][q])
		return true;
	return false;
}
 
bool dfs(int qx, int qy, int low, int high)
{
	if(qx==r-1 and qy==c-1)
	{
		if(low>ar[qx][qy])
			return false;
		if(high<ar[qx][qy])
			return false;
		return true;
	}
	/*if(t>=2)
		printf("%d %d with %d %d\n", qx, qy, min_, max_);*/
	bool br = false;
	int nx, ny;
 
	for(int j=0;j<4;j++)
	{
		nx = qx+dx[j];
		ny = qy+dy[j];
		if(valid(nx, ny))
		{
			if(low>ar[nx][ny])
				continue;
			if(high<ar[nx][ny])
				continue;
			vis[nx][ny] = true;
			br = br or dfs(nx, ny, low, high);
			if(br)
				return true;
		}
	}
	return false;
}
 
int main()
{
	int i, j, k, a, b, bomb;
	int ans;
	scanf("%d", &r);
	c = r;
 
	a= INF;
	b = -INF;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			scanf("%d", &ar[i][j]);
			a = min(a, ar[i][j]);
			b = max(b, ar[i][j]);
		}
 
	int qx, qy;
	int nx, ny;
	bool status = false;
 
	a= 0;
	b= 110;
	t=0;
	while(t<=110)
	{
		for(i=a, j=a+t; j<=b; i++, j++)
		{
			status = false;
			if(ar[0][0]<i or ar[0][0]>j)
				continue;
			
			for(k=0;k<r;k++)
				for(int l=0;l<c;l++)
					vis[k][l]=false;
			vis[0][0] = true;
 
			status = dfs(0, 0, i, j);
			if(status)
				break;
		}
		if(status)
			break;
		t++;
	}
	assert(t<=110);
	printf("%d\n", t);
		
	return 0;
}
