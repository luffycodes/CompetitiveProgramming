#include<stdio.h>
 
long long fib[30][30];
long long tmp[30][30];
long long res[30][30];
long long val[30];
 
void fib_fn(int n, int limit, int MOD)
{
	int i, j, k;
	i = limit;
	for(i=0;i<limit;i++)
		for(j=0;j<limit;j++)
			fib[i][j]=0;
	for(j=0;j<limit;j++)
		fib[0][j] = 1;
	for(i=1;i<limit;i++)
		fib[i][i-1]=1;
	
	for(i=0;i<limit;i++)
		for(j=0;j<limit;j++)
			res[i][j]=0;
	for(i=0;i<limit;i++)
		res[i][i]=1;
			
	while(n)
	{
		if(n&1)
		{
			for(i=0;i<limit;i++)
				for(j=0;j<limit;j++) 
					tmp[i][j]=0;
					
			for(i=0;i<limit;i++)
				for(j=0;j<limit;j++) 
					for(k=0;k<limit;k++)
						tmp[i][j]=(tmp[i][j]+res[i][k]*fib[k][j])%MOD;
						
			for(i=0;i<limit;i++) 
				for(j=0;j<limit;j++) 
					res[i][j]=tmp[i][j];
		}
		
		for(i=0;i<limit;i++)
			for(j=0;j<limit;j++)
				tmp[i][j]=0;
				
		for(i=0;i<limit;i++) 
			for(j=0;j<limit;j++) 
				for(k=0;k<limit;k++)
				   tmp[i][j]=(tmp[i][j]+fib[i][k]*fib[k][j])%MOD;
				   
		for(i=0;i<limit;i++) 
			for(j=0;j<limit;j++) 
				fib[i][j]=tmp[i][j];
		n/=2;
 
	}
	return;
}
 
int main()
{
	long long a, b;
	int i, j, n, k, l, t, mod;
	//for(i=0;i<30;i++)
	//	for(j=0;j<30;j++)
	//		exp[i][j]=0;
			
	//for(i=0;i<30;i++)
	//	exp[0][i]=exp[i][0]=1;
	//intialised the fibonacci exponentiation matrix
	
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d %d", &n, &k, &l);
		mod = 1;
		while(k--)
			mod = mod*10;
		//printf("%d\n", 
		if(l<n)
			printf("%d\n", l%mod);
		else
		{
			fib_fn(l-n+1, n, mod);
			for(i=0;i<n;i++)
				val[i]=n-i-1;
			a=0;
			for(i=0;i<n;i++)
				a = (a+res[0][i]*val[i])%mod;
			printf("%lld\n", a%mod);
		}
	}
	return 0;
} 
