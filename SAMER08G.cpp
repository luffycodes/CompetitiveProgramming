#include<stdio.h>
 
int main()
{
	int i, j, temp, n, possible;
	int ar[1000];
	scanf("%d", &n);
	while(n!=0)
	{
		possible = 1;
		for(i=0;i<n;i++)
			ar[i]=0;
		for(i=0;i<n;i++)
		{
			scanf("%d %d", &temp, &j);
			if(i+j>=n||i+j<0)
				possible = 0;
			else
			{
				if(ar[i+j]!=0)
					possible = 0;
				else
					ar[i+j] = temp;
			}
		}
		if(possible==1)
			for(i=0;i<n;i++)
			{
				printf("%d", ar[i]);
				if(i<n)
					printf(" ");
			}
		else
			printf("-1");
		printf("\n");
		scanf("%d", &n);
	}
	return 0;
}
