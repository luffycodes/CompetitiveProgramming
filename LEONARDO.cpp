#include<stdio.h>
 
using namespace std;
 
int main()
{
	int i, j, k, t, n;
	bool seen[26], yes;
	char in[30];
	int perm[26], cnt[30];
	
	scanf("%d", &t);
	while(t--)
	{
		yes = true;
		scanf("%s", &in);
		for(i=0;i<26;i++)
			perm[i]=in[i]-'A';
		for(i=0;i<26;i++)
			seen[i]=false;
		for(i=0;i<30;i++)
			cnt[i]=0;
		for(i=0;i<26;i++)
		{
			if(!seen[i])
			{
				k = perm[i];
				n=1;
				while(k!=i)
				{
					seen[k]=true;
					n++;
					k = perm[k];
				}
				cnt[n]++;
			}
		}
		for(i=2;i<30;i+=2)
		{
			if(cnt[i]%2==1)
				yes = false;
		}
		if(yes)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
