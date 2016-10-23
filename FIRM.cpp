#include<stdio.h>
 
int ar[5010];
bool vis[5010];
int first[10010];
int second[10010];
int chain[5010];
 
int N, T, l1=0, l2=0;
 
int cycle(int idx)
{
	int l = 0, i;
	while(!vis[idx])
	{
		vis[idx] = true;
		chain[l++] = ar[idx];
		idx = ar[idx];
	}
	/*for(i=0; i<l; i++)
		printf("%d ", chain[i]);
	printf("\n");*/
	return l;
}
 
void one()
{
	first[2*l1] = chain[0];
	first[2*l1+1] = chain[1];
	l1++;
}
 
void two(int len)
{
	int i, j;
	for(i=0, j=len-1; i<j; i++, j--)
	{
		first[2*l1] = chain[i];
		first[2*l1+1] = chain[j];
		chain[i] = first[2*l1+1];
		chain[j] = first[2*l1];
		l1++;
	}
	for(i=1, j=len-1; i<j; i++, j--)
	{
		second[2*l2] = chain[i];
		second[2*l2+1] = chain[j];
		l2++;
	}
}
 
int main()
{
	int i, j, len;
	scanf("%d", &N);
	for(i=0; i<N; i++)
		scanf("%d",&ar[i+1]);
		
	for(i=0; i<=N; i++)
		vis[i]=false;
				
	for(i=1; i<=N; i++)
	{
		if(vis[i])
			continue;
		len = cycle(i);
		if(len==2)
			one();
		else 
			two(len);
	}
	if(l1==0)
		printf("0\n");
	else if(l2==0)
	{
		printf("1\n%d ", l1);
		for(i=0; i<l1; i++)
		{
			printf("%d-%d", first[2*i], first[2*i+1]);
			if(i<l1-1)
				printf(" ");
			else	
				printf("\n");
		}
	}
	else
	{
		printf("2\n%d ", l1);
		for(i=0; i<l1; i++)
		{
			printf("%d-%d", first[2*i], first[2*i+1]);
			if(i<l1-1)
				printf(" ");
			else
				printf("\n");
		}
		printf("%d ", l2);
		for(i=0; i<l2; i++)
		{
			printf("%d-%d", second[2*i], second[2*i+1]);
			if(i<l2-1)
				printf(" ");
			else
				printf("\n");
		}
	}
}
