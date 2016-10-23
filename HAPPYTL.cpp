#include <cstdio>
 
using namespace std;
 
#define MAX 10010
int start[MAX], end[MAX];
 
int main(){
	int N, M, K;
	int src, dest;
	scanf("%d %d", &N, &M);
	while(N!=0 or M!=0){
		for(int i=0;i<N;i++){
			scanf("%d %d %d %d", &src, &dest, &start[i], &end[i]);
			end[i]+=start[i];
		}
		int ans;
		//scanf("%d", &K);
		while(M--){
			ans = 0;
			scanf("%d %d", &src, &dest);
			dest += src;
			for(int i=0;i<N;i++){
				if(src>=end[i] or dest<=start[i])
					continue;
				else
					ans++;
			}
			printf("%d\n", ans);
		}
		scanf("%d %d", &N, &M);
	}
	return 0;
}
