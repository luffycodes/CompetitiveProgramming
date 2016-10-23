#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
 
using namespace std;
 
#define N 1000000
 
bool a[N];
vector <long long> primes;
vector <long long> pfactor;
vector <int> ppower;
vector <long long> factors;
set <long long> pfacset;
 
void sieve() {
	for(int i = 2; i < N; i ++) {
		if(!a[i]) {
				primes.push_back((long long) i);
				for(int j = 2 * i; j < N; j += i)
					a[j] = true;
		}
	}
}
 
void factorize(long long n) {
	for(int i = 0; i < primes.size(); i ++) {
		if(n % primes[i] == 0) {
			pfacset.insert(primes[i]);
			int pow = 0;
			while(n % primes[i] == 0) {
				n /= primes[i];
				pow ++;
			}
			pfactor.push_back(primes[i]);
			ppower.push_back(pow);
		}
	}
	if(n != 1) {
		pfactor.push_back(n), ppower.push_back(1);
		pfacset.insert(n);
	}
}
 
void work(long long curr, int ind) {
	if(ind == pfactor.size()) {
		if(pfacset.count(curr) == 0)
			factors.push_back(curr);
		return;
	}
	long long multi = 1;
	for(int i = 0; i <= ppower[ind]; i ++) {
		work(curr * multi, ind + 1);
		multi = multi * pfactor[ind];
	}
}
 
int main() {
	sieve();
	int T;
	cin >> T;
	while(T -- > 0) {
		long long n;
		cin >> n;
		if(n & 1LL) {
			printf("0\n");
			continue;
		}
		factorize(n / 2);
		work(1, 0);
		sort(factors.begin(), factors.end());
		cout << factors.size() << " ";
		for(int i = 0; i < factors.size(); i ++)
			cout << factors[i] << " ";
		cout << "\n";
		pfactor.clear();
		ppower.clear();
		factors.clear();
		pfacset.clear();
	}
	return 0;
}
