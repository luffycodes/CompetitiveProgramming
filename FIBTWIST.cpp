#include<stdio.h>
 
long long fib_fn(int n, int MOD)
{
	long long int fib[2][2]={{1,1},{1,0}},ret[2][2]={{1,0},{0,1}},tmp[2][2]={{0,0},{0,0}};
	int i, j, k;
	while(n)
	{
		if(n&1)
		{
			for(i=0;i<2;i++)
				for(j=0;j<2;j++)
					tmp[i][j]=0;
			for(i=0;i<2;i++) for(j=0;j<2;j++) for(k=0;k<2;k++)
					tmp[i][j]=(tmp[i][j]+ret[i][k]*fib[k][j])%MOD;
			for(i=0;i<2;i++) for(j=0;j<2;j++) ret[i][j]=tmp[i][j];
		}
		for(i=0;i<2;i++)
				for(j=0;j<2;j++)
					tmp[i][j]=0;
		for(i=0;i<2;i++) for(j=0;j<2;j++) for(k=0;k<2;k++)
							   tmp[i][j]=(tmp[i][j]+fib[i][k]*fib[k][j])%MOD;
					for(i=0;i<2;i++) for(j=0;j<2;j++) fib[i][j]=tmp[i][j];
		n/=2;
 
	}
	return (ret[0][1])%MOD;
}
 
int main()
{
	int i, j, k, t;
	long long n, m, ans;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld %lld", &n, &m);
		ans = fib_fn(n+2, m);
		ans = ans-1;
		while(ans<0)
			ans = ans+m;
		ans = 2*(ans)%m;
		ans = ans-n;
		while(ans<0)
			ans = ans+m;
		printf("%lld\n", ans);
	}
	return 0;
}
