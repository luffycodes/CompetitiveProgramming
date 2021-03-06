#include <cstdio>
#include <stack>
#include <algorithm>
#include <cstring>
#include <cassert>
 
using namespace std;
 
#define N 4000
 
stack <int> height, ind;
 
int a[N + 1];
 
int work(int n)
{
	int Max = 0;
	/*for(int i = 0; i < n; i ++)
		printf("%d ", a[i]);
	printf("\n");*/
	for(int i = 0; i < n; i ++)
	{
		if(height.empty())
		{
			height.push(a[i]);
			ind.push(i);
			continue;
		}
		int h = height.top();
		if(a[i] > h)
		{
			height.push(a[i]);
			ind.push(i);
			continue;
		}
		if(a[i] < h)
		{
			int lastin;
			while(!height.empty() && height.top() > a[i])
			{
				int p = height.top(), in = ind.top();
				lastin = in;
				Max = max(Max, max(p * (i - in), a[i]* (i - in + 1)));
				height.pop();
				ind.pop();
			}
			if(!height.empty() && a[i] == height.top())
				continue;
			height.push(a[i]);
			ind.push(lastin);
		}
	}
	//assert(height.empty());
	return Max;
}
 
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int m, n, f;
		scanf("%d %d", &n, &m);
		if(n == 0)
			return 0;
		int ans = 0;
		memset(a, 0, sizeof(a));
		char temp[N + 1];
		for(int i = 0; i < n; i ++)
		{
			//f = strlen(temp);
			//printf("%s\n", temp);
			for(int j = 0; j < m; j=j+1)
			{
				scanf("%s", temp);
				if(temp[0] == 'F')
					a[j]++;
				else
					a[j] = 0;
			}
			a[m] = 0;
			ans = max(ans, work(m + 1));
		}
		printf("%lld\n", ((long long) ans) * ((long long)3));
	}
}
