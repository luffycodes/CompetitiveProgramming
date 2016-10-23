#include<stdio.h>
 
int main()
{
	int ar[11][11];
	int i, j, k, t, n, m, p;
	bool c1, c2, c3, cc2, cc3, cc1;
	scanf("%d" ,&t);
	for(i=0;i<t;i++)
	{
		scanf("%d %d",&n, &p);
		c1=c2=c3=false;
		cc2 = cc3 = true;
		for(j=0;j<n;j++)
		{
			c2 = false;
			c3 = false;
			for(k=0;k<p;k++)
			{
				scanf("%d", &ar[j][k]);
				if(ar[j][k]==1)
					c2 = true;
				else
					c3 = true;
			}
			if(c2==false)
				cc2 = false;
			if(!c3)
				cc3 = false;
		}
		cc1 = true;
		for(j=0;j<p;j++)
		{
			c1 = false;
			for(k=0;k<n;k++)
				if(ar[k][j]==1)
					c1 = true;
			if(!c1)
				cc1 = false;
		}
		if(cc1&&cc2&&cc3)
			printf("Case %d: 7\n", i+1);
		else if(cc1&&cc2&&!cc3)
			printf("Case %d: 6\n", i+1);
		else if(cc1&&!cc2&&cc3)
			printf("Case %d: 5\n", i+1);
		else if(cc1&&!cc2&&!cc3)
			printf("Case %d: 4\n", i+1);
		else if(!cc1&&cc2&&cc3)
			printf("Case %d: 3\n", i+1);
		else if(!cc1&&cc2&&!cc3)
			printf("Case %d: 2\n", i+1);
		else if(!cc1&&!cc2&&cc3)
			printf("Case %d: 1\n", i+1);
		else if(!cc1&&!cc2&&!cc3)
			printf("Case %d: 0\n", i+1);
	}
	return 0;
}
