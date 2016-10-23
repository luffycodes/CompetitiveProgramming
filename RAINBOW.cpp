#include<stdio.h>
#include<string.h>
 
using namespace std;
 
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}
 
const int maxsize=1000+5;
 
int n,m;
int f[maxsize];
int father[maxsize];
int A[maxsize];
 
int getfather(int v)
{
	return (father[v]<0)?v:(father[v]=getfather(father[v]));
}
 
void merge(int u,int v)
{
	u=getfather(u);
	v=getfather(v);
	if (u!=v) father[u]=v;
}
 
int main()
{
	while (scanf("%d%d",&n,&m)!=-1 && n!=0)
	{
		memset(father,255,sizeof(father));
		for (int i=1;i<=n;i++) scanf("%d",&A[i]);
		for (int i=1;i<=n;i++)
		{
			int cnt;
			scanf("%d",&cnt);
			for (;cnt>0;cnt--)
			{
				int value;
				scanf("%d",&value);
				merge(i,value);
			}
		}
		memset(f,0,sizeof(f));
		for (int i=1;i<=n;i++) 
			if (father[i]<0)
			{
				int cnt=0;
				int sum=0;
				for (int j=1;j<=n;j++) 
					if (getfather(j)==i)
						cnt++,sum+=A[j];
				for (int k=m;k>=sum;k--)
					checkmax(f[k],f[k-sum]+cnt);
			}
		printf("%d\n",f[m]);
	}
	return 0;
}
