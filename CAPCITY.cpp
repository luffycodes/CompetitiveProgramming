#include <stdio.h>
#include <stack>
#include <vector>
#include <algorithm>
 
using namespace std;
 
#define MAX 100010
 
int n, m, currDfn, currScc;
stack<int> Stack;
vector<int> graph[MAX];
bool vis[MAX], inStack[MAX], isRootOfDag[MAX];
int dfn[MAX], hno[MAX], scc[MAX], cntScc[MAX];
 
void Dfs(int v)
{
	int i, w;
	
	vis[v] = true;
	dfn[v] = ++currDfn;
	hno[v] = dfn[v];
	Stack.push(v);
	inStack[v] = true;
	
	for (i=0; i<graph[v].size(); i++)
	{
		if (not vis[graph[v][i]])
		{
			Dfs(graph[v][i]);
			hno[v] = min(hno[v], hno[graph[v][i]]);
		}
		else if (inStack[graph[v][i]])
			hno[v] = min(hno[v], dfn[graph[v][i]]);
	}
	
	if (dfn[v] == hno[v])
	{
		++currScc;
		w = Stack.top();
		while (w != v)
		{
			scc[w] = currScc;
			cntScc[currScc]++;
			Stack.pop();
			inStack[w] = false;
			w = Stack.top();
		}
		scc[w] = currScc;
		cntScc[currScc]++;
		Stack.pop();
		inStack[w] = false;
	}
}
 
void Scc()
{
	int i;
	
	for (i=1; i<=n; i++)
	{
		vis[i] = inStack[i] = false;
		isRootOfDag[i] = true;
		cntScc[i] = 0;
	}
	currDfn = currScc = 0;
	while (not Stack.empty())
		Stack.pop();
	
	for (i=1; i<=n; i++)
		if (not vis[i])
			Dfs(i);
}
 
int main()
{
	int t;
	int i, j, k, cnt, ver, a, b;
	
	scanf("%d %d", &n, &m);
	for (i=1; i<=m; i++)
	{
		scanf("%d %d", &a, &b);
		graph[b].push_back(a);
	}
	Scc();
	
	for (i=1; i<=n; i++)
		for (j=0; j<graph[i].size(); j++)
			if (scc[i] != scc[graph[i][j]])
				isRootOfDag[scc[graph[i][j]]] = false;
	
	bool flag = true;
	int ans = -1;
	int cno;
	for (i=1; i<=currScc; i++)
	{
		if (isRootOfDag[i])
		{
			if (flag)
			{
				ans = cntScc[i];
				cno = i;
				flag = false;
			}
			else
			{
				ans = 0;
				break;
			}
		}
	}
	
	printf("%d\n", ans);
	for(i=1;i<=n;i++)
	{
		if(scc[i]==cno)
			printf("%d ", i);
	}
	printf("\n");
	return 0;
}
