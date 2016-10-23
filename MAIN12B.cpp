#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
 
#define no 1000001
 
using namespace std;
 
int main()
{
	bool ar[no];
	int primes[no/10];
	bool print[no/10];
	long long input[110];
	long long rest[110];
	int ans, d;
	int i, j, pr=0, t, n, r, k;
	for(i=2;i<no;i++)
     	ar[i]=true;
		
	primes[pr++]=2;
	
	for(i=3;i<no;i+=2)
		if(ar[i])
		{
			primes[pr++] = i;
			for(j=i*i;j>0&&j<no;j+=i)
				ar[j]=false;
		}
		
	scanf("%d", &t);
	for(int tt=1;tt<=t;tt++)
	{
		for(i=0;i<pr;i++)
			print[i]=false;
		r=0;
		ans=0;
		scanf("%d", &n);
		for(i=0;i<n;i++)
			scanf("%lld", &input[i]);
		
		for(i=0;i<n;i++)
		{
			for(j=0;j<pr;j++)
			{
				if(!print[j])
				{
					if(input[i]%primes[j]==0)
					{
						print[j]=true;
						ans++;
						while(input[i]%primes[j]==0)
							input[i]/=primes[j];
					}
				}
				else
				{
					while(input[i]%primes[j]==0)
							input[i]/=primes[j];
				}
			}
			if(input[i]>no)
			{
				rest[r++] = input[i];
				ans++;
			}
		}
		sort(rest+0, rest+r);
		//d = rest[0];
		for(i=1;i<r;i++)
		{
			if(rest[i]==rest[i-1])
			{
				ans--;
				rest[i-1]=0;
			}
		}
		printf("Case #%d: %d\n", tt, ans);
		for(i=0;i<pr;i++)
		{
			if(print[i])
				printf("%d\n", primes[i]);
		}
		for(i=0;i<r;i++)
		{
			if(rest[i]>0)
				printf("%lld\n", rest[i]);
		}
	}
	return 0;
}
