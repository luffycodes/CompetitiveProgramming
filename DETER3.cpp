# include <cstdio>
# include <algorithm>
# include <vector>
# include <cstring>
using namespace std;
 
typedef long long int64;
 
const int MAX_N = 200;
 
int64 pow_bin(int64 x, int64 n, int64 mod = 0x7fffffff) {
 int64 ret = 1;
 for(; n; n >>= 1) {
	 if(n & 1) {
		 ret = ret * x% mod;
	 }
	 x = x * x% mod;
 }
 
 return ret;
}
 
int64 extgcd(int64 a, int64 b, int64 & x, int64 & y) {
 int64 d = a;
 if(b!= 0) {
	 d = extgcd(b, a% b, y, x);
	 y -=(a/b) * x;
 }
 else {
	 x = 1;
	 y = 0;
 }
 return d;
}
 
int64 mod_inv(int64 a, int64 mod) {
 int64 x, y;
 extgcd(a, mod, x, y);
 return(x% mod + mod)% mod;
}
 
pair <int64, int64> chinese_remainder(const vector <int64> & as, const vector <int64> & ms) {
 int64 x = 0, mod = 1;
 
 for(int i = 0; i <(int) as.size(); i++) {
	 int64 a = as[i] - x, d = __gcd(ms[i], mod);
	 if(a%d!= 0) {
		 return make_pair(0, - 1);
	 }
	 int64 t = a/d * mod_inv(mod/d, ms[i]/d)%(ms[i]/d);
	 x = x + mod * t;
	 mod *= ms[i]/d;
 }
 
 return make_pair((x + mod)% mod, mod);
}
 
namespace determinant_integer {
 
 const int MAX_N = :: MAX_N;
 int64 mat[MAX_N][MAX_N], mat_tmp[MAX_N][MAX_N];
 
 int64 determinant_modulo_prime(const int n, const int64 p, const int e = 1) {
	 int64 ret = 1;
	 const int64 mod = pow_bin(p, e);
 
	 // Take the modulo of the elements to nonnegative
	 for(int i = 0; i <n; i++) {
		 for(int j = 0; j <n; j++) {
			 mat[i][j]%= mod;
			 if(mat[i][j] <0) {
				 mat[i][j] += mod;
			 }
		 }
	 }
 
	 for(int i = 0; i <n; i++) {
 
		 // Normalize looking for a pivot
		 int pivot = - 1;
		 int64 inv = - 1;
		 int mini = 0xff;
		 for(int j = i; j <n; j++) {
			 if(mat[j][i]!= 0) {
				 if(e == 1) {
					 pivot = j;
					 break;
				 }
				 else {
					 int64 x = mat[j][i];
					 int cnt = 0;
					 for(; x% p == 0; x/= p, cnt++);
					 if(cnt <mini) {
						 mini = cnt;
						 pivot = j;
					 }
				 }
			 }
		 }
 
		 if(pivot == - 1) {
			 return 0;
		 }
 
		 if(pivot!= i) {
			 ret = mod - ret;
			 for(int j = i; j <n; j++) {
				 swap(mat[pivot][j], mat[i][j]);
			 }
		 }
 
		 if(e == 1) {
			 ret = ret * mat[i][i]% mod;
			 inv = pow_bin(mat[i][i], mod - 2, mod);
		 }
		 else {
			 int64 rem = mat[i][i]/pow_bin(p, mini);
			 ret = ret * rem% mod;
			 inv = mod_inv(rem, mod);
		 }
 
		 for(int j = i; j <n; j++) {
			 mat[i][j] = mat[i][j] * inv% mod;
		 }
 
		 // Draw a line normalized
		 for(int j = i + 1; j <n; j++) {
			 int64 mul = mat[j][i]/mat[i][i];
			 for(int k = i; k <n; k++) {
				 mat[j][k] -= mul * mat[i][k]% mod;
				 if(mat[j][k] <0) {
					 mat[j][k] += mod;
				 }
			 }
		 }
	 }
 
	 // Take the product of the diagonal elements
	 for(int i = 0; i <n; i++) {
		 ret = ret * mat[i][i]% mod;
	 }
 
	 return ret;
 }
 
 int64 determinant(const int n, const int64 mod) {
	 if(mod == 1) {
		 return 0;
	 }
	 vector <int64> ms, es, ps;
	 // Factoring mod
	 int64 m = mod;
	 for(int64 i = 2; i * i <= m; i++) {
		 if(m% i == 0) {
			 ms.push_back(i);
			 es.push_back(0);
			 while(m% i == 0) {
				 es.back()++;
				 m/= i;
			 }
		 }
	 }
	 if(m!= 1) {
		 ms.push_back(m);
		 es.push_back(1);
	 }
 
	 for(int i = 0; i <(int) ms.size(); i++) {
		 ps.push_back(pow_bin(ms[i], es[i]));
	 }
 
	 // Calculate the matrix equation for each prime number should be
	 vector <int64> as(ms.size());
	 for(int i = 0; i <(int) as.size(); i++) {
		 memcpy(mat_tmp, mat, sizeof(mat));
		 as[i] = determinant_modulo_prime(n, ms[i], es[i]);
		 // Printf("mod:%lld, det:%lld \n", ps[i], as[i]);
		 memcpy(mat, mat_tmp, sizeof(mat));
	 }
 
 
	 // Restore
	 return (chinese_remainder(as, ps).first + mod)% mod;
 }
}
 
using determinant_integer :: determinant;
using determinant_integer :: determinant_modulo_prime;
using determinant_integer :: mat;
 
int N;
int64 P;
 
bool init() {
 if(scanf("%d %lld", & N, & P) == EOF) {
	 return false;
 }
 
 for(int i = 0; i <N; i++) {
	 for(int j = 0; j <N; j++) {
		 scanf("%lld", mat[i] + j);
	 }
 }
 
 return true;
}
 
int solve() {
 return(int) determinant(N, P);
}
 
int main() {
 
 while(init()) {
	 printf("%d \n", solve());
 }
 
 return 0;
}
