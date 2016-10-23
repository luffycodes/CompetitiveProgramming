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
	#include <stack>
 
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
 
#define pb push_back
#define mp make_pair
 
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
 
const double PT = acos(-1.0);
const double EPS = 1e-11;
 
#define MAX 11
#define INF 10000000
 
int N, M;
vector<pair <int, PII > > roads;
int Ri[MAX];
int Pi[MAX];
int dp[1<<MAX][MAX];
 
int solve(){
	int pa, pcost;
	int na, ncost;
	int inter;
	int pmask, nmask;
 
	REP(i, 1<<N)
		REP(j, N)
			dp[i][j] = INF;
 
	set <pair <int, PII> > S;
	pair <int, PII> temp;
 
	dp[1][0]=0;
	REP(i, 1<<N)
		REP(j, N)
			S.insert(mp(dp[i][j],mp(j,i)));
 
	//printf("%d %d\n", dp[1][N-1], dp[2][N-1]);
	while(!S.empty()){
		temp = *S.begin();
		S.erase(S.begin());
		pcost = temp.first;
		pa = temp.second.first;
		pmask = temp.second.second;
 
		REP(i, M){
			if(roads[i].first!=pa) //this edge doesnot originate from here
				continue;
			na = roads[i].second.first;
			inter = roads[i].second.second;
			ncost = Ri[i];
			nmask = pmask | (1<<na);
 
			if(pmask & (1<<inter)){
				//printf("%d to %d via %d with %d at %d\n", pa, na, inter,\
				//	pmask, pcost);
				ncost = min(ncost, Pi[i]);
			}
			if(ncost + pcost < dp[nmask][na]){
				S.erase(S.find(mp(dp[nmask][na], mp(na, nmask))));
				S.insert(mp(ncost+pcost, mp(na, nmask)));
				dp[nmask][na] = ncost+pcost;
			}
		}
	}
 
	int ans = INF;
	REP(i, 1<<N){
		//printf("%d %d\n", i, dp[i][N-1]);
		ans = min(ans, dp[i][N-1]);
	}
	return ans;
}
 
int main(){
	int a, b, c;
 
	scanf("%d %d", &N, &M);
	REP(i, M){
		scanf("%d %d %d %d %d", &a, &b, &c, &Pi[i], &Ri[i]);
		roads.pb(mp(a-1, mp(b-1,c-1)));
	}
	int ans = INF;
	ans =  solve();
	if(ans==INF){
		printf("impossible\n");
	}
	else
		printf("%d\n", ans);
	return 0;
}
