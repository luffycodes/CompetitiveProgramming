#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
 
using namespace std;
 
struct plank{
	int x;
	int y;
};
 
bool operator<(const plank& a,const plank& b)
{
	if(a.y>b.y)
		return true;
	return false;
}
 
#define MAXN 10020
 
plank inp[MAXN];
int order[MAXN];
//bool nail[MAXN];
int n, m, s, t;
 
bool cmp(int a, int b)
{
	if(inp[a].x < inp[b].x)
		return true;
	return false;
}
 
int main()
{
	int i, j, k, T, cnt;
	int a, b, c, ans;
	scanf("%d", &T);
	while(T--)
	{
		/*for(i=0; i<MAXN; i++)
			nail[i]=false;
*/
		scanf("%d", &n);
		for(i=0; i<n; i++)
		{
			scanf("%d %d", &a, &b);
			inp[i].x = a;
			inp[i].y = b;
			order[i]=i;
		}
		sort(order, order+n, cmp);
	/*	for(i=0;i<n; i++)
			printf("(%d, %d)\n", inp[order[i]].x, inp[order[i]].y);*/
 
		int cnt=1;
		priority_queue<plank> q;
		plank temp;
		ans=0;
 
		q.push(inp[order[0]]);
		//printf("Pushing (%d,%d)\n", inp[order[0]].x, inp[order[0]].y);
 
		while(cnt<n)
		{
			temp = q.top();
			//printf("top is (%d, %d)\n", temp.x, temp.y);
			if(inp[order[cnt]].x <= temp.y) //the newest planks a is smaller than the earliest b in q
			{
				q.push(inp[order[cnt]]);
			//	printf("Pushing (%d,%d)\n", inp[order[cnt]].x, inp[order[cnt]].y);
			}
			else	//you have to empty the queue now
			{
				ans++;
				while(!q.empty())
				{
					//temp = q.top();
					//vis[order[temp]]=true;
					q.pop();
				}
				q.push(inp[order[cnt]]);
			//	printf("Pushing (%d,%d)\n", inp[order[cnt]].x, inp[order[cnt]].y);
			}
			cnt++;
		}
		if(q.size()>0)
			ans++;
		printf("%d\n", ans);
	}
	return 0;
} 
