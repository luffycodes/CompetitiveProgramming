#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <math.h>
#include <cassert>
 
using namespace std;
 
#define DEBUG if(0)
 
//Numberic Functions
template<class T> inline T gcd(T a, T b){
	if(a<0)return gcd(-a,b); if(b<0)return gcd(a,-b); return (b==0)?a:gcd(b,a%b);
}
template<class T> inline T lcm(T a, T b){
	if(a<0)return lcm(-a,b); if(b<0)return lcm(a,-b); return a*(b/gcd(a,b));
}
template<class T> inline T euclide(T a, T b, T &x, T &y){
	if(a<0){T d=euclide(-a,b,x,y); x=-x; return d;}
	if(b<0){T d=euclide(a,-b,x,y); y=-y; return d;}
	if(b==0){x=1;y=0;return a;}else{T d=euclide(b,a%b,x,y);T t=x;x=y;y=t-(a/b)*y;return d;}
}
 
template<class T> inline bool isPrimeNumber(T n){
	if(n<=1)return false;for(T i=2;i*i<=n;i++) if(n%i==0) return false;return true;
}
template<class T> inline T eularFunction(T n){
	vector<pair<T,int> > R=factorize(n);T r=n;for (int i=0;i<R.size();i++)r=r/R[i].first*(R[i].first-1);return r;
}
 
//Translator
bool isUpperCase(char c){return c>='A' && c<='Z';}
bool isLowerCase(char c){return c>='a' && c<='z';}
bool isLetter(char c){return c>='A' && c<='Z' || c>='a' && c<='z';}
bool isDigit(char c){return c>='0' && c<='9';}
char toLowerCase(char c){return (isUpperCase(c))?(c+32):c;}
char toUpperCase(char c){return (isLowerCase(c))?(c-32):c;}
 
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define FOR(i, s, e) for(int i = (int)(s); i < (int)(e); i++)
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
 
#define pb push_back
#define mp make_pair
 
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
 
const double PT = acos(-1.0);
const double EPS = 1e-11;
 
#define MAXN 27
#define MAXT (1<<12)
 
struct node{
	int x;
	int y;
	int ti;
};
 
int N;
 
bool vis[MAXT][MAXN][MAXN];
char init[MAXN][MAXN], t[MAXN][MAXN];
 
int dx[] = {0, 0, 0, -1, 1};
int dy[] = {0, 1, -1, 0, 0};
 
bool valid(int x, int y, int ti){
	if(x>=0 and x<N and y>=0 and y<N){
		int c = t[x][y] - '0';
		DEBUG
		printf("At %d %d with time %d and c %d ", x, y, ti, c);
		
		if(c==0){
			if(init[x][y]=='*'){
				DEBUG
					printf("Char is *\n");
				return false;
			}
			else{
				DEBUG
					printf("Char is .\n");
				return true;
			}
		}else{
			ti = ti/c;
			if(ti%2==0){
				if(init[x][y]=='*'){
					DEBUG
						printf("Char is *\n");
					return false;
				}
				else{
					DEBUG
						printf("Char is .\n");
					return true;
				}
			}else{
				if(init[x][y]=='.'){
					DEBUG
						printf("Char is *\n");
					return false;
				}
				else{
					DEBUG
						printf("Char is .\n");
					return true;
				}
			}
		}
	}
	else
		return false;
}
 
int main(){
	int i, j, k, T;
 
	queue<node> q;
	node tmp;
	int ans;
 
	int qx, qy, qt;
	int nx, ny, nt;
 
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		REP(i, N)
			scanf("%s", init[i]);
		REP(i, N)
			scanf("%s", t[i]);
 
		FOR(i, 0, MAXT)
			REP(j, N)
				REP(k, N)
					vis[i][j][k] = false;
 
		if(init[0][0]=='*'){
			printf("NO\n");
			continue;
		}
		else{
			while(!q.empty())
				q.pop();
 
			q.push((node){0, 0, 0});
			vis[0][0][0] = true;
			ans = MAXT;
		}
 
		while(!q.empty()){
			tmp = q.front();
			q.pop();
 
			if(tmp.x == N-1 and tmp.y == N-1){
				ans = tmp.ti;
				break;
			}
			if(tmp.ti == MAXT)
				break;
 
			qx = tmp.x, qy = tmp.y, qt = tmp.ti;
 
			//DEBUG
			//	printf("At %d %d with time %d\n", qx, qy, qt);
 
			REP(i, 5){
				nx = qx + dx[i];
				ny = qy + dy[i];
				nt = qt + 1;
				if(valid(nx, ny, nt) and !vis[nt][nx][ny]){
					q.push((node){nx, ny, nt});
					vis[nt][nx][ny] = true;
				}
 
			}
		}
		if(ans!=MAXT)
			printf("%d\n", ans);
		else
			printf("NO\n");
	}
	return 0;
} 
