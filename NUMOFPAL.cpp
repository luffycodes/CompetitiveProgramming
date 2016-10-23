#include<stdio.h>
#include<string.h>
 
using namespace std;
 
int main()
{
	char ar[1010];
	int i, j, l, k, ans;
	scanf("%s", &ar);
	l = strlen(ar);
	
	ans=0;
	for(i=0; i<l; i++)
	{
		for(j=0;;j++)
		{
			if(i-j<0)
				break;
			if(i+j>=l)
				break;
			if(ar[i-j]==ar[i+j])
				ans++;
			else
				break;
		}
	}
	for(i=0, k=i+1; k<l; i++, k++)
	{
		for(j=0;;j++)
		{
			if(i-j<0)
				break;
			if(k+j>=l)
				break;
			if(ar[i-j]==ar[k+j])
				ans++;
			else
				break;
		}
	}
	printf("%d\n", ans);
	return 0;
} 
