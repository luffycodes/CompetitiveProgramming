#include<stdio.h>
 
typedef long long LL;
 
LL ar[1001][1001], temp;
LL val[1001][1001];
 
LL get(int n,int a)
{
	if(n<a) return val[a][n];
	int q = n / a;
	LL r = (1ll*a*q*(q-1))/2 + 1ll*val[a][a-1]*q; 
	return r + 1ll*q*(n%a+1) + val[a][n%a];
}
 
int main()
{
	int i, j, k, t, m, n, p, q;
	LL rat;
	ar[0][0]=ar[0][1]=ar[1][0]=0LL;
	ar[1][1]=1LL;
	for(i=1;i<1001;i++)
		for(j=i;j<1001;j++)
			ar[i][j] = ar[j][i] = j/i+ ar[j%i][i];
	for(i=0;i<1001;i++)
	{
		val[i][0]=0LL;
		for(j=1;j<1001;j++)
			val[i][j] = val[i][j-1]+ar[i][j];
	}
	/*for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			printf("len = %d, bre= %d, no: %lld\n", i, j, ar[i][j]);*/
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d %d %d", &m, &n, &p, &q);
		temp =0LL;
		for(i=p;i<=q;i++)
		{
			temp+=get(n, i) - get(m-1, i);
		}	
		printf("%lld\n", temp);
	}
	return 0;
}
