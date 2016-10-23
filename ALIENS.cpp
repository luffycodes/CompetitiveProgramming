#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
 
using namespace std;
 
#define EPS 1e-7
 
struct point {
  double first;
  double second;
};
 
struct circle {
  struct point c;
  double r;
};
 
int N;
struct point X[100000];
 
inline int dbl_less_or_eq(double a, double b) {
  if(a < b + EPS) {
    return 1;
  } else {
    double mag = (a + b) / 2.0 * EPS;
    return a < b + mag;
  }
} //checks if double values a and b are equal or less -PJ
 
inline double dist(struct point* A, struct point* B) {
  return sqrt((A->first -  B->first ) * (A->first  - B->first ) +
              (A->second - B->second) * (A->second - B->second));
} //computes distance between 2 points
 
struct circle two_points(struct point* A, struct point* B) {
  struct circle ret;
  ret.c = *A;
  ret.c.first += B->first;
  ret.c.second += B->second;
  ret.c.first /= 2;
  ret.c.second /= 2;
  ret.r = dist(&ret.c, A);
  return ret;
} //construt the circle from 2 points
 
double cp(struct point* A, struct point* B, struct point* C) {
  return (B->first - A->first) * (C->second - A->second) -
         (C->first - A->first) * (B->second - A->second);
}
 
int bsz = 0;
struct point* border[2];
 
struct circle mec(int n) 
{
	struct circle res;
	double rr;
	int i, j;
	if(bsz == 0) 
	{
		if(n == 0) 
		{
			res.c.first = 0;
			res.c.second = 0;
			res.r = 0;
		}
		else if(n == 1) 
		{
			res.c = *X;
			res.r = 0;
		}
		else
			res = two_points(X, X + 1);
	}
	else if(bsz == 1) 
	{
		if(n == 0) 
		{
			res.c = *border[0];
			res.r = 0;
		}
		else
			res = two_points(border[0], X);
 
	}
	else if(bsz == 2)
	{
		struct point* a = border[0];
		struct point* b = border[1];
		double A[3][2];
		double b0, lo, hi, mid;
 
		A[0][0] = a->first - b->first;
		A[0][1] = a->second - b->second;
		A[2][0] = a->second - b->second;
		A[2][1] = b->first - a->first;
		b0 = (a->first + b->first) * A[0][0] / 2.0 + (a->second + b->second) * A[0][1] / 2.0;
 
		lo = -1e300;
		hi = 1e300;
		for(i = 0; i < 1; i++) 
		{
			double b1, det, c;
			A[1][0] = b->first - X[i].first;
			A[1][1] = b->second - X[i].second;
			b1 = (X[i].first + b->first) * A[1][0] / 2.0 + (X[i].second + b->second) * A[1][1] / 2.0;
			det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
		
			if(dbl_less_or_eq(fabs(det), 0))
			// It's impossible for X[i] to be anywhere but inbetween a and b.
				continue;
 
			c = A[2][0] * (b0 * A[1][1] / det - b1 * A[0][1] / det) + A[2][1] * (b1 * A[0][0] / det - b0 * A[1][0] / det);
			if(det > 0) 
			{
				if(c > lo)
					lo = c;
			}
			else
			{
				if(c < hi)
					hi = c;
			}
		}
		mid = A[2][0] * a->first + A[2][1] * a->second;
		if(dbl_less_or_eq(lo, mid) && dbl_less_or_eq(mid, hi))
			res = two_points(a, b);
		else
		{
			double b1, det;
			b1 = fabs(lo - mid) < fabs(hi - mid) ? lo : hi;
			det = A[0][0] * A[2][1] - A[0][1] * A[2][0];
			res.c.first = b0 * A[2][1] / det - b1 * A[0][1] / det;
			res.c.second = b1 * A[0][0] / det - b0 * A[2][0] / det;
			res.r = dist(&res.c, a);
		}
		return res;
	}
 
	rr = res.r * res.r;
	for(i = 0; i < n; i++) 
	{
		double dx, dy;
		dx = res.c.first - X[i].first;
		dy = res.c.second - X[i].second;
 
		if(!dbl_less_or_eq(dx * dx + dy * dy, rr))
		{
			struct point tmp = X[i];
			border[bsz++] = X + i;
			res = mec(i);
			rr = res.r * res.r;
			for(j = i; j; j = j >> 1)
				X[j] = X[j >> 1];
		
			*X = tmp;
			bsz--;
		}
	}
	return res;
}
 
int main() 
{
	int T, t, i;
	scanf("%d", &T);
	for(t = 1; t <= T; t++) 
	{
		scanf("%d", &N);
		for(i = 0; i < N; i++) 
			scanf("%lf %lf", &X[i].first, &X[i].second);
		
		struct circle crc = mec(N);
		printf("%.2f\n%.2f %.2f\n", crc.r, crc.c.first, crc.c.second);
	}
	return 0;
}
