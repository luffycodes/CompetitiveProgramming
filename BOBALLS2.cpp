#include <stdio.h>
#include <algorithm>
 
#define MAXN 3010
 
using namespace std;
 
class Ball
{
	public:
	int x, y;
	int vx, vy;
};
Ball balls[MAXN], ans[MAXN];
 
bool operator<(const Ball& a, const Ball& b)
{
	if (a.x == b.x and a.y == b.y)
		return false;
	if (a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}
 
int main()
{
	int X, Y, N, M;
	long long t;
	int i, j, tMod2X, tMod2Y, temp;
 
	scanf("%d %d", &X, &Y);
	scanf("%d", &N);
	for (i=0; i<N; i++)
		scanf("%d %d %d %d", &balls[i].x, &balls[i].y, &balls[i].vx, &balls[i].vy);
	scanf("%d", &M);
	while (M--)
	{
		scanf("%lld", &t);
		tMod2X = t%(2*X);
		tMod2Y = t%(2*Y);
		for (i=0; i<N; i++)
		{
			temp = (balls[i].x + balls[i].vx*tMod2X + 2*X)%(2*X);
			if (temp > X)
				ans[i].x = X - temp%X;
			else
				ans[i].x = temp;
			temp = (balls[i].y + balls[i].vy*tMod2Y + 2*Y)%(2*Y);
			if (temp > Y)
				ans[i].y = Y - temp%Y;
			else
				ans[i].y = temp;
		}
		sort(ans, ans+N);
		for (i=0; i<N; i++)
			printf("%d %d\n", ans[i].x, ans[i].y);
		printf("\n");
	}
 
	return 0;
}
