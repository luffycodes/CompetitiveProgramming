#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
 
using namespace std;
 
struct doll{
	int w, h;
	bool operator<(const doll &p) const{
		//SORT in decreasing height and for the same height on increasing width
		if(h!=p.h)
			return h>p.h;
		return w<p.w;
	}
};
 
bool cmp(doll a, doll b){
	return a.w < b.w;
}
 
doll d[20005];
 
int main(){
	int T, M;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &M);
		for(int i=0;i<M;i++){
			scanf("%d %d", &d[i].w, &d[i].h);
		}
		sort(d, d+M);
		
		int ans = M;
		doll *last = d;
		doll *it;
		for(int i=0;i<M;i++){
			//printf("%d %d\n", d[i].w, d[i].h);
			it = upper_bound(d, last, d[i], cmp);
			if(it!=last){
				//we found a doll in which this can be added
				ans--;
				it->w = d[i].w;
			}else{
				*(last++) = d[i];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
