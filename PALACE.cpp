#include<stdio.h>
 
int main()
{
	int t, n, i, j;
	int ans[204];
	ans[0]=1;
	for(i=1;i<204;i++)
		ans[i] = (2*ans[i-1])%98777;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d",&n);
		n--;
		printf("%d\n", ans[((n%204)*(n%204))%204]);
	}
	return 0;
}
