#include <algorithm>
#include <cstdio>
#include <cstring>
 
using namespace std;
 
const int MAXN = 333, MAXM = 111111, INF = 1000000000;
 
int tot, s, t, n, m, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];
 
inline void addedge(int x, int y, int z) {
    p[tot] = y;
    c[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot++;
}
 
inline bool bfs() {
    memset(d, -1, sizeof d);
    int r = d[q[0] = s] = 0;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (c[k] && !~d[p[k]])
                d[q[++r] = p[k]] = d[q[l]] + 1;
    return ~d[t];
}
 
int dfs(int x, int ext) {
    if (x == t)
        return ext;
    int flow, ret = 0;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(c[k], ext)))) {
            ret += flow;
            c[k] -= flow;
            c[k ^ 1] += flow;
            if (!(ext -= flow))
                return ret;
        }
    return ret;
}
 
inline void work() {
    int ans = tot = 0;
    t = n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        if (x) {
            addedge(s, i, 1);
            addedge(i, s, 0);
        }
        else {
            addedge(i, t, 1);
            addedge(t, i, 0);
        }
    }
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y, 1);
        addedge(y, x, 1);
    }
    while (bfs()) {
        memcpy(g, h, sizeof h);
        ans += dfs(s, INF);
    }
    printf("%d\n", ans);
}
 
int main() {
    while (scanf("%d%d", &n, &m) && n)
        work();
    return 0;
}
