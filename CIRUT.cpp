#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
const double eps = 1e-08;
const double pi = 3.14159265358979;
double tau;
inline int fi (double a)
{
    if (a > eps) return 1;
    else if (a >= -eps) return 0;
    else return -1;
}
typedef pair<double, double> interval;
inline interval redi (interval a)
{
    if (fi(a.first) == -1) return make_pair(a.first + tau, a.second + tau);
    else return a;
}
struct circle
{
    double x, y, r;
    circle (void) {}
    circle (double x0, double y0, double r0) : x(x0), y(y0), r(r0) {}
};
inline int judge (const circle& a, const circle& b)
{
    double dx = b.x - a.x, dy = b.y - a.y;
    double d = sqrt(dx * dx + dy * dy);
    if (fi(a.r + b.r - d) <= 0) return 1;
    else if (fi(a.r + d - b.r) <= 0) return 2;
    else if (fi(b.r + d - a.r) <= 0) return 3;
    else return 0;
}
inline interval intersect (const circle& a, const circle& b)
{
    double dx = b.x - a.x, dy = b.y - a.y;
    double d = dx * dx + dy * dy;
    double ag = atan2(dy, dx);
    double tg = acos((a.r * a.r + d - b.r * b.r) / (2 * a.r * sqrt(d)));
    return redi(make_pair(ag - tg, ag + tg));
}
circle list[1010]; int cover[1010], n;
const int ending = -10010;
struct rec
{
    double ang; int pwr;
    rec (void) {}
    rec (double a0, int p0) : ang(a0), pwr(p0) {}
    bool operator < (const rec& a) const
    {
        if (fi(ang - a.ang)) return fi(ang - a.ang) == -1;
        else return pwr > a.pwr;
    }
} key[5010]; int keymr;
inline double cal (const circle& c, double a0, double a1)
{
    double da = a1 - a0;
    if (fi(da) == 0) return 0;
    double px0 = c.x + c.r * cos(a0);
    double py0 = c.y + c.r * sin(a0);
    double px1 = c.x + c.r * cos(a1);
    double py1 = c.y + c.r * sin(a1);
    double s = c.r * c.r * (da - sin(da)) + (px0 * py1 - px1 * py0);
    return s; 
}
double ans[1010];
void stat (int cnt)
{
    keymr = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == cnt) continue;
        int res = judge(list[cnt], list[i]);
        if (res == 2) ++cover[cnt];
        else if (res == 0)
        {
            interval tt = intersect(list[cnt], list[i]);
            if (fi(tau - tt.second) == -1)
            {
                key[keymr++] = rec(tt.first, 1);
                key[keymr++] = rec(tau, -1);
                key[keymr++] = rec(0, 1);
                key[keymr++] = rec(tt.second - tau, -1);
            }
            else
            {
                key[keymr++] = rec(tt.first, 1);
                key[keymr++] = rec(tt.second, -1);
            }
        }
    }
    if (keymr == 0)
    {
        double tt = pi * list[cnt].r * list[cnt].r * 2;
        ans[cover[cnt]] -= tt;
        ans[cover[cnt] + 1] += tt;
    }
    else
    {
        key[keymr++] = rec(0, 0);
        key[keymr++] = rec(tau, ending);
        sort(key, key + keymr);
        int stack = 0;
        for (int i = 0; i < keymr - 1; i++)
        {
            stack += key[i].pwr;
            double tt = cal(list[cnt], key[i].ang, key[i + 1].ang);
            ans[cover[cnt] + stack] -= tt;
            ans[cover[cnt] + stack + 1] += tt;
        }
    }
}
int main ()
{
    tau = pi * 2.0;
    int cnt; scanf("%d", &cnt), n = 0;
    for (int i = 0; i < cnt; i++)
    {
        int x0, y0, r0;
        scanf("%d %d %d", &x0, &y0, &r0);
        if (r0) list[n++] = circle(x0, y0, r0);
    }
    memset(cover, 0, sizeof cover);
    memset(ans, 0, sizeof ans);
    for (int i = 0; i < n; i++) stat(i);
    for (int i = 1; i <= n; i++) printf("[%d] = %.3f\n", i, ans[i] / 2);
    return 0;
}
