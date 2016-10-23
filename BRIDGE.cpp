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
 
#define MAXN 1010
 
PII ar[MAXN];
VI inp;
VI lis;
 
void find_lis(vector<int> &a, vector<int> &b){
    vector<int> p(a.size());
    int u, v;
 
    if (a.empty()) return;
 
    b.push_back(0);
 
    for (size_t i = 1; i < a.size(); i++){
                // If next element a[i] is greater than (pj: or equal) last element of current longest subsequence a[b.back()], just push it at back of "b" and continue
        if (a[b.back()] <= a[i]){
            p[i] = b.back();
            b.push_back(i);
            continue;
        }
 
                // Binary search to find the smallest element referenced by b which is just bigger than a[i]
                // Note : Binary search is performed on b (and not a). Size of b is always <=k and hence contributes O(log k) to complexity.    
        for (u = 0, v = b.size()-1; u < v;){
            int c = (u + v) / 2;
            if (a[b[c]] <= a[i]) u=c+1; else v=c;
        }
 
                // Update b if new value is smaller then previously referenced value 
        if (a[i] <= a[b[u]]) {
            if (u > 0) p[i] = b[u-1];
            b[u] = i;
        }   
    }
 
    for (u = b.size(), v = b.back(); u--; v = p[v]) b[u] = v;
}
 
//LIS()
 
int main(){
    int i, j, k, t, T, cnt, n;
 
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        REP(i, n){
          scanf("%d", &k);
          ar[i].first = k;
        }
          
        REP(i, n){
          scanf("%d", &k);
          ar[i].second = k;
        }
 
        sort(ar, ar+n);
 
        inp.clear();
        lis.clear();
 
        REP(i, n){
          inp.pb(ar[i].second);
        }
 
        find_lis(inp, lis);
 
        printf("%d\n", lis.size());
    }
    return 0;
}
