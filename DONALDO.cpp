#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include<string.h>
 
using namespace std;
 
#define MAX 20010
 
struct Node
{
	int time;
};
typedef Node Node;
 
Node nodes[MAX];
 
bool cmp(Node a, Node b)
{
	return a.time < b.time;
}
 
int convert(char *input)
{
	int time = 0, i = 0, temp = 0;
	while (input[i] != ':')
	{
		temp = temp*10 + (input[i]-'0');
		i++;
	}
	time += temp * 3600;
	temp = 0;
	i++;
	while (input[i] != ':')
	{
		temp = temp*10 + (input[i]-'0');
		i++;
	}
	time += temp * 60;
	temp = 0;
	i++;
	while (input[i] != '\0' and i<10)
	{
		temp = temp*10 + (input[i]-'0');
		i++;
	}
	time += temp;
	return time;
}
 
int search(int total, int key)
{
	int start = 0, end = total-1, mid;
 
	while(start < end-1)
	{
		mid = (start + end)/2;
		if (nodes[mid].time <= key)
			start = mid;
		else
			end = mid-1;
	}
	if (end>=0 and nodes[end].time <= key)
		return end;
	if (nodes[start].time <= key)
		return start;
 
	//assert(false);
	return -1;
}
 
void PrintNodes(int total)
{
	int i;
	for (i=0; i<total; i++)
		printf("%d\n", nodes[i].time);
}
 
int main()
{
	int T, N, l, len;
	int i, j, ans, temp;
	char input[10];
 
	scanf("%d", &T);
	for (i=1; i<=T; i++)
	{
		scanf("%d", &N);
		for (j=0; j<N; j++)
		{
			scanf("%s", input);
			len = strlen(input);
			//assert(len>=5);
			nodes[j].time = convert(input);
		}
		scanf("%d", &l);
		if (N == 0)
		{
			printf("Case %d: 0\n", i);
			continue;
		}
 
		sort(nodes, nodes+N, cmp);
		
		//PrintNodes(N);
 
		ans = 0;
		for (j=0; j<N; j++)
		{
			temp = search(N, nodes[j].time+l-1);
			if(temp>=0)
				ans = max(ans, temp-j+1);
		}
		printf("Case %d: %d\n", i, ans);
	}
 
	return 0;
} 
