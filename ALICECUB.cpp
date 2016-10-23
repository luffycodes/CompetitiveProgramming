
#include <stdio.h>
#include <queue>
 
using namespace std;
 
int powers[17];
int adj[][5] = {{0,0,0,0,0}, {2,3,5,9,0}, {4,6,10,0,0}, {4,7,11,0,0}, {8,12,0,0,0}, {6,7,13,0,0}, {8,14,0,0,0}, {8,15,0,0,0}, {16,0,0,0,0},
   				{10,11,13,0,0},	{12,14,0,0,0}, {12,15,0,0,0}, {16,0,0,0,0}, {14,15,0,0,0}, {16,0,0,0,0}, {16,0,0,0,0}, {0,0,0,0,0}};
int graph[17][17];
queue< pair<int,int> > q;
 
void prepare()
{
	int i, j;
 
	for (i=1; i<=16; i++)
		for (j=1; j<=16; j++)
			graph[i][j] = 0;
 
	for (i=1; i<=16; i++)
		for (j=0; adj[i][j] != 0; j++)
			graph[i][adj[i][j]] = graph[adj[i][j]][i] = 1;
 
	powers[0] = 1;
	for (i=1; i<=16; i++)
		powers[i] = powers[i-1] * 2;
}
 
bool check(int input)
{
	int i;
 
	for (i=0; i<8; i++)
		if (((int)(input & powers[i])) == 0)
			return false;
	for (i=8; i<=15; i++)
		if (((int)(input & powers[i])) != 0)
			return false;
	return true;
}
 
// Assumes that check(test) = false.
bool predict(int input)
{
	int i, a = -1, b = -1;
 
	for (i=0; i<8; i++)
	{
		if (((int)input & powers[i]) == 0)
		{
			if (b >= 0)
				return false;
			b = 16 - i;
		}
	}
	for (i=8; i<=15; i++)
	{
		if (((int)input & powers[i]) != 0)
		{
			if (a >= 0)
				return false;
			a = 16 - i;
		}
	}
 
	if (graph[a][b] == 1)
		return true;
	return false;
}
 
int Search(int input)
{
	pair<int,int> p;
	int i, j, a, b, newNum;
	
	if (check(input))
		return 0;
 
	while (not q.empty())
		q.pop();
	q.push(make_pair(input,0));
 
	while(not q.empty())
	{
		p = q.front();
		q.pop();
 
		if (predict(p.first))
			return p.second+1;
		if (p.second < 2)
		{
			for (i=1; i<=16; i++)
			{
				a = ((int)(p.first & powers[16-i]));
				for (j=0; adj[i][j] != 0; j++)
				{
					b = ((int)(p.first & powers[16-adj[i][j]]));
					if (a == 0 and b != 0)
					{
						newNum = p.first + powers[16-i] - powers[16-adj[i][j]];
						q.push(make_pair(newNum, p.second+1));
					}
					else if (a != 0 and b == 0)
					{
						newNum = p.first - powers[16-i] + powers[16-adj[i][j]];
						q.push(make_pair(newNum, p.second+1));
					}
				}
			}
		}
	}
	return 100;
}
 
int main()
{
	int i, j, T;
	int ans, num, temp;
 
	prepare();
	scanf("%d", &T);
	for (i=1; i<=T; i++)
	{
		num = 0;
		for (j=15; j>=0; j--)
		{
			scanf("%d", &temp);
			num += temp*powers[j];
		}
 
		ans = Search(num);
		if (ans <= 3)
			printf("Case #%d: %d\n", i, ans);
		else
			printf("Case #%d: more\n", i);
	}
 
	return 0;
}
