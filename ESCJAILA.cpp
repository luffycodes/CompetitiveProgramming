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
#include <string.h>
 
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
 
#define MAXM 101
 
int N, M;
char ar[MAXM][MAXM];
int vis[MAXM][MAXM][2];
 
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
 
bool valid(int n, int m, int t){
	if(n<0 or n>=N or m<0 or m>=M)
		return false;
	if(ar[n][m]=='W' or vis[n][m][t]>0)
		return false;
	if(ar[n][m]=='D' and t==0)
		return false;
	return true;
}
 
bool ex(int n, int m){
	if((n<0 or n==N) or (m<0 or m==M))
		return true;
	return false;
}
 
void solve(){
	REP(i, N)
		REP(j, M)
			vis[i][j][0]= vis[i][j][1] = -1;
 
	int hx, hy;
	REP(i, N)
		REP(j, M)
			if(ar[i][j]=='H'){
				hx = i;
				hy = j;
				ar[i][j]='.';
				break;
			}
 
	queue<int> Q;
	Q.push(hx);
	Q.push(hy);
	Q.push(0);
	Q.push(0);
	vis[hx][hy][0] = 0;
 
	int x, y, t, c;
	int nx, ny, nt, nc;
 
	while(!Q.empty()){
		x = Q.front(), Q.pop();
		y = Q.front(), Q.pop();
		c = Q.front(), Q.pop();
		t = Q.front(), Q.pop();
 
		//printf("Got to %d %d with type %d and cost %d\n", x, y, t, c);
 
		if(x==-1 and y==-1){
			printf("%d\n", c);
			return;
		}
 
		if(ar[x][y]=='C')
			nt = 0;
		else if(ar[x][y]=='O')
			nt = 1;
		else
			nt = t;
 
		nc = c+1;
 
		REP(i, 4){
			nx = x + dx[i];
			ny = y + dy[i];
			
			//printf("Trying %d %d with type %d and cost %d\n", nx, ny, nt, nc);
 
			if(valid(nx, ny, nt)){
				//printf("Pushing %d %d with type %d and cost %d\n", nx, ny, nt, nc);
				Q.push(nx);
				Q.push(ny);
				Q.push(nc);
				Q.push(nt);
				vis[nx][ny][nt] = nc;
				//printf("Pushed %d %d with type %d and cost %d\n", nx, ny, nt, nc);
			}
			else if(ex(nx, ny)){
				//printf("Pushing %d %d with type %d and cost %d\n", -1, -1, 0, nc);
				Q.push(-1);
				Q.push(-1);
				Q.push(nc);
				Q.push(0);
				//printf("Pushed %d %d with type %d and cost %d\n", -1, -1, 0, nc);
			}
		}
 
	}
	printf("-1\n");
	return;
}
 
 
int main(){
	int i, j, k, t, T, cnt;
	
	scanf("%d %d", &N, &M);
	while(N>0 and M>0){
 
		REP(i, N)
			scanf("%s", ar[i]);
 
		solve();
 
		scanf("%d %d", &N, &M);
	}
	return 0;
}
