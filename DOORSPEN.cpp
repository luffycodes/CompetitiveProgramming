#include <stdio.h>
#include <algorithm>
#include <math.h>
#include "vector"
 
using namespace std;
 
#define PI 3.141592653589793
#define EPS 0.0000000001
 
struct pt {
	int x, y;
};
 
bool cmp (pt a, pt b) {
	return a.x <b.x || a.x == b.x && a.y <b.y;
}
 
bool cw (pt a, pt b, pt c) {
	return a.x * (b.y-c.y) + b.x * (c.y-a.y) + c.x * (a.y-b.y) <0;
}
 
bool ccw (pt a, pt b, pt c) {
	return a.x * (b.y-c.y) + b.x * (c.y-a.y) + c.x * (a.y-b.y)> 0;
}
 
void convex_hull (vector <pt> & a) {
	if (a.size () == 1) return;
	sort (a.begin (), a.end (), & cmp);
	pt p1 = a [0], p2 = a.back ();
	vector <pt> up, down;
	up.push_back (p1);
	down.push_back (p1);
	for (size_t i = 1; i <a.size (); ++i) 
	{
		if (i == a.size () -1 || cw (p1, a [i], p2)) 
		{
			while (up.size ()>= 2 && !cw (up [up.size () -2], up [up.size () -1], a[i]))
				up.pop_back ();
			up.push_back (a [i]);
		}
		if (i == a.size () -1 || ccw (p1, a [i], p2)) 
		{
			while (down.size ()>= 2 && !ccw (down [down.size () -2], down [down.size () -1], a [i]))
				down.pop_back ();
			down.push_back (a [i]);
		}
	}
	a.clear ();
	for (size_t i = 0; i <up.size (); ++i)
		a.push_back (up [i]);
	for (size_t i = down.size () -2; i> 0; --i)
		a.push_back (down [i]);
}
 
double angle(pt &a,pt &b,pt &c)
{
    double ux = b.x-a.x,uy =b.y - a.y;
    double vx = c.x-a.x,vy =c.y - a.y;
    return acos((ux*vx+uy*vy)/sqrt((ux*ux+uy*uy)*(vx*vx+vy*vy)));
}
 
int cross(int x1, int y1, int x2, int y2)
{
	return x1*y2 - y1*x2;
}
 
bool inPolygon(pt &p, vector<pt> polygon)
{
    int n = (int)polygon.size();
    if(n==0)
    	return false;
    double sum=0.0;
    pt pp, ppp;
    for(int i=0;i<n-1;i++)
    {
        pp = polygon[i];
        ppp= polygon[i+1];
 
        if(cross(pp.x-p.x, pp.y-p.y, ppp.x-p.x, ppp.y-p.y) <= 0)
            sum-=angle(p,pp,ppp);
        else 
        	sum+=angle(p,pp,ppp);
    }
    pp = polygon[n-1];
    ppp = polygon[0];
    if(cross(pp.x-p.x, pp.y-p.y, ppp.x-p.x, ppp.y-p.y) <= 0)
        sum-=angle(p,pp,ppp);
    else 
        sum+=angle(p,pp,ppp);
 
    return fabs(sum-2*PI) < EPS || fabs(sum+2*PI) < EPS;
 
}
 
int main()
{
	vector<pt> ptdoor;
	vector<pt> ptpen;
	vector<pt> conv_door;
	vector<pt> conv_pen;
 
	bool check;
 
	int i, n, d, p, t=1;
	int x1, x2, y1, y2;
	scanf("%d %d", &d, &p);
	while(d!=0 and p!=0)
	{
		ptdoor.clear();
		ptpen.clear();
		conv_pen.clear();
		conv_door.clear();
		check = true;
		for(i=0;i<d;i++)
		{
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			pt p1;
			p1.x = x1, p1.y =y1;
			pt p2;
			p2.x = x2, p2.y =y2;
			pt p3;
			p3.x = x1, p3.y =y2;
			pt p4;
			p4.x = x2, p4.y =y1;
			ptdoor.push_back(p1);
	        ptdoor.push_back(p2);
	        ptdoor.push_back(p3);
	        ptdoor.push_back(p4);
	        conv_door.push_back(p1);
	        conv_door.push_back(p2);
	        conv_door.push_back(p3);
	        conv_door.push_back(p4);
		}
		convex_hull(conv_door);
		
		for(i=0;i<p;i++)
		{
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			if(check)
			{
				pt p1;
				p1.x = x1, p1.y =y1;
				pt p2;
				p2.x = x2, p2.y =y2;
				pt p3;
				p3.x = x1, p3.y =y2;
				pt p4;
				p4.x = x2, p4.y =y1;
				ptpen.push_back(p1);
		        ptpen.push_back(p2);
		        ptpen.push_back(p3);
		        ptpen.push_back(p4);
		        conv_pen.push_back(p1);
		        conv_pen.push_back(p2);
		        conv_pen.push_back(p3);
		        conv_pen.push_back(p4);
		        if(inPolygon(p1, conv_door) || inPolygon(p2, conv_door) || inPolygon(p3, conv_door) || inPolygon(p4, conv_door))
		        	check = false;
		    }
		}
		if(check)
		{
			convex_hull(conv_pen);
			for(i=0; i<ptdoor.size(); i++)
			{
				if(inPolygon(ptdoor[i], conv_pen))
				{	check = false;
					break;
				}
			}
		}
		if(check)
			printf("Case %d: It is possible to separate the two groups of vendors.\n",t++);
		else
			printf("Case %d: It is not possible to separate the two groups of vendors.\n",t++);
		scanf("%d %d", &d, &p);
	}
	return 0;
}  
