#include<stdio.h>
#include<math.h>
 
int main()
{
	int i, j, k, l, t, sq;
	unsigned long long x, y, z, disc, ans, temp;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%llu %llu %llu", &x, &y, &z);
		disc = y*y + x*x + 2*y*z;
		if(disc>0)
			sq = (int)sqrt((long long)disc);
		else 
			sq = 0;
		temp = sq;
		if(temp*temp==disc)
		{
			temp = z*temp;
			ans = temp + x*z;
			if((ans%(y+2*z))==0)
				printf("%llu\n", ans/(y+2*z));
			else
			{
				ans = x*z - z*temp;
				if((ans%(y+2*z))==0)
					printf("%llu\n", ans/(y+2*z));
				else
					printf("Not this time.\n");
			}
		
		}
		else
			printf("Not this time.\n");
	}
	return 0;
} 
