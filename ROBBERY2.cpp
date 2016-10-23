#include<stdio.h>
#include<math.h>
 
int main()
{
	int t, k, temp, i, j, unc;
	long long n, rounds, temp_l, left, ans;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld %d", &n, &k);
		temp_l = (sqrt(8*n-3));
		temp_l = (temp_l - 3)/2;
		while((temp_l*(temp_l+1)>2*n)||((temp_l+1)*(temp_l+2)<=2*n))
		{
			if(temp_l*(temp_l+1)>2*n)
				temp_l--;
			else if((temp_l+1)*(temp_l+2)<2*n)
				temp_l++;
		}
		rounds = temp_l/k;
		unc = temp_l%k;
		left = n - temp_l*(temp_l+1)/2;
		temp_l = rounds*k;
		for(i=1;i<=k;i++)
		{
			ans = i*rounds + (rounds*(rounds-1)/2)*k;
			if(i<=unc)
				ans = ans + temp_l+i;
			else if(i==unc+1)
				ans = ans+left;
			printf("%lld", ans);
			if(i<k)
				printf(" ");
		}
		printf("\n");
	}
	return 0;
} 
