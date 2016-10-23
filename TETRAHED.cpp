#include<stdio.h>
#include<algorithm>
 
using namespace std;
 
int a[3], b[3], c[3], d[3], e[3];
int ar1[3], ar2[3], ar3[3];
 
int dete(int *x, int* y, int* z)
{
	return (x[0]*(y[1]*z[2] - y[2]*z[1]) - x[1]*(y[0]*z[2] - y[2]*z[0]) + x[2]*(y[0]*z[1] - y[1]*z[0]));
}
 
int vol(int* p, int* q, int* r,int* s)
{
	int i;
	int x[3], y[3], z[3];
	for(i=0;i<3;i++)
		x[i] = p[i]-q[i];
	for(i=0;i<3;i++)
		y[i] = q[i]-r[i];
	for(i=0;i<3;i++)
		z[i] = r[i]-s[i];
	//printf("%d %d %d\n", p[0], q[1], r[2]);
	return dete(x, y, z);
}
 
int main()
{
	int i, j, k, l, t, n, m, max;
	scanf("%d", &t)	;
	while(t--)
	{
		scanf("%d %d %d", &a[0], &a[1], &a[2]);
		scanf("%d %d %d", &b[0], &b[1], &b[2]);
		scanf("%d %d %d", &c[0], &c[1], &c[2]);
		scanf("%d %d %d", &d[0], &d[1], &d[2]);
		scanf("%d %d %d", &e[0], &e[1], &e[2]);
		n = abs(vol(a, b, c, d));
		m = abs(vol(a, b, c, e));
		if(m>n)
		{
			max = m;
			l = 4;
		}
		else
		{
			max = n;
			l = 5;
		}
		m = abs(vol(a, b, d, e));
		if(m>max)
		{
			max = m;
			l = 3;
		}
		m = abs(vol(a, c, d, e));
		if(m>max)
		{
			max = m;
			l = 2;
		}
		m = abs(vol(b, c, d, e));
		if(m>max)
		{
			max = m;
			l = 1;
		}
		printf("%d\n", l);
	}
	return 0;
} 
