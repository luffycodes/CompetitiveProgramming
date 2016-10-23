#include <cstdio>
 
using namespace std;
 
#define M 30
#define N 100001
 
int anc[N][M], a[N], s[N];
 
int find_anc(int u, unsigned int m) {
	if(m == 0)
		return u;
	int power = 31 - __builtin_clz(m);
	unsigned int toTake = ((unsigned int) 1) << power;
	return find_anc(anc[u][power], m - toTake);
}
 
void init(int n, unsigned int m) {
	for(int k = 0; (((unsigned int) 1) << k) <= m; k ++) {
		for(int i = 0; i < n; i ++) {
			if(k == 0) {
				anc[i][k] = a[i];
			}
			else {
				anc[i][k] = anc[anc[i][k - 1]][k - 1];
			}
		}
	}
}
 
int main() {
	int n, k;
	unsigned int m;
	scanf(" %d %d %u", &n, &k, &m);
	for(int i = 0; i < n; i ++) {
		scanf(" %d", s + i);
		s[i] --;
	}
	for(int i = 0; i < k; i ++) {
		scanf(" %d", a + i);
		a[i] --;
	}
	init(k, m);
	for(int i = 0; i < n; i ++) {
		printf("%d ", find_anc(s[i], m - 1) + 1);
	}
	return 0;
}
