#include<stdio.h>
 
int main()
{
	int n, t, ans, temp, i;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		ans = 5;
		for(i=1;i<n;i++)
			ans = (ans*10)%314159;
		temp = 4;
		for(i=1;i<n;i++)
			temp = (temp*8)%314159;
		ans = (ans + temp)%314159;
		printf("%d\n", ans);
	}
	return 0;
}
