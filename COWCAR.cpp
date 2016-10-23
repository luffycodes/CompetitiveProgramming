#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int Maxcows();
 
int n,m,d,l;
vector<int> speeds;
int main(){
	scanf("%d %d %d %d",&n,&m,&d,&l);
	int s;
	for(int i=0;i<n;i++){
		scanf("%d",&s);
		speeds.push_back(s-l);
	}
	sort(speeds.begin(),speeds.begin()+speeds.size());
	int ans = Maxcows();
	printf("%d\n",ans);
}
 
int Maxcows(){
	int rank = 0;
	int count = 0;
	int pointer = 0;
	while(true){
		int j=0;	
		while(j<m){
			if(pointer>=speeds.size()) return count;
			
			int element = speeds[pointer];
			pointer++;
			
			if(element-rank*d>=0){
				count ++;
				j++;
			}
		}
		rank ++;
	}
	return count;
}
