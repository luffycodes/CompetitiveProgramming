#include<stdio.h>
#include<iostream>
#include<assert.h>
 
using namespace std;
#define MAX 10000
bool isprimes[MAX];
int primes[MAX];
int pcount;
 
void makeseive(){
	pcount = 0;
	for(int i=0;i<MAX;i++)isprimes[i]=true;
	for(int i=2;i<MAX;i++){
		if(!isprimes[i])continue;
		primes[pcount] = i;
		pcount++;
		for(int j=1;j*i<MAX;j++)isprimes[j*i] = false;
	}
}
 
int n;
int factors(int n){
	while(n%2==0)n=n/2;
	int count = 1,p,result = 1,mul;
	while(n>1 && count < pcount){
		mul = 0;
		p = primes[count];
		assert(p>1);
		while(n%p==0)
		{
			n = n/p;
			mul++;
			//assert(n>0);
		}
		result = result*(mul+1);
		count++;
	}
	if(n!=1)result = result *2;
	return result;
}
 
int main(){
	makeseive();
	while(true){
		scanf("%d",&n);
		if(n==0)break;
		int num = factors(n);
		printf("%d\n",2*num);
	}
	return 0;
} 
