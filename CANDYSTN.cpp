#include <stdio.h>
#include <algorithm>
 
using namespace std;
 
#define MAX 10005
 
int milestones[MAX];
 
int main()
{
	int T, N, M;
	int i, bag, coll, minCol, minBag;
	int ans;
	
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &N, &M);
		for (i=0; i<M; i++)
			scanf("%d", &milestones[i]);
 
		bag = N, coll = 0;
		minBag = N, minCol = 0;
		for (i=1; i<M; i++)
		{
			if (milestones[i] == milestones[i-1])
				coll--;
			else
			{
				coll += milestones[i] - milestones[i-1];
				bag -= milestones[i] - milestones[i-1];
			}
			minCol = min(minCol, coll);
			minBag = min(minBag, bag);
		}
		ans = 1 - minCol;
		if (minBag - ans < 0)
			ans = -1;
		printf("%d\n", ans);
	}
 
	return 0;
}
