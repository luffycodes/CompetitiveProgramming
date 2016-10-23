#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
 
struct point{
	int sum,modulo;
};
 
int n;
//bool visited[1001][1001];
int parent[1001][1001][2],mlook[1010][10],mod0[11010];
 
void bfs()
{
	queue<point> Q;
	point tmp;
		tmp.sum=0;
		tmp.modulo=0;
		Q.push(tmp);
	int it=0;
	while(!Q.empty())
	{
		point p=Q.front();
		Q.pop();
		//printf("%d\n",it++);
		if (p.sum==n && p.modulo==0)
		{
			//visited[p.sum][p.modulo]=true;
			break;
		}
		for(int i=0;i<=9;i++)
		{
			point tmp;
			tmp.sum=p.sum+i;
			tmp.modulo=mlook[p.modulo][i];
			if(tmp.sum<=n && parent[tmp.sum][tmp.modulo][0]==-1 && parent[tmp.sum][tmp.modulo][1]==-1 )
			{
				Q.push(tmp);
				//visited[tmp.sum][tmp.modulo]=true;
				parent[tmp.sum][tmp.modulo][0]=p.sum;
				parent[tmp.sum][tmp.modulo][1]=p.modulo;
			}
		}
	}
	//printf("exited bfs\n");
	
}
 
int main()
{
	int t;
	scanf("%d",&t);
	int arr[2000];
	char s[2000];
	while(t--)
	{
		scanf("%d",&n);
		//memset(visited,false,sizeof(visited));
		memset(parent,-1,sizeof(parent));
		/*memset(mod0,-1,sizeof(mod0));
		for (int i=0;i<=10;i++)
		{
			mod0[n*i]=0;
			for (int j=1;j<n;j++)
				mod0[n*i+j]=mod0[n*i+j-1]+1;
		}*/
		for(int i=0;i<=n;i++)for(int j=0;j<10;j++)mlook[i][j]=(i*10+j)%n;
		/*for (int i=0;i<=n;i++)for(int j=0;j<=n;j++){
			parent[i][j][0]=parent[i][j][1]=-1;
			//visited[i][j]=0;
		}*/
		//visited[0][0]=true;
		parent[0][0][0]=-2;
		int tm;
		point tmp;
		bfs();
		if(parent[n][0][0]!=-1)
		{
			
			int c=0;
//			printf("true\n");
			tmp.sum=n;
			tmp.modulo=0;
			while(parent[tmp.sum][tmp.modulo][0]!=-2)
			{
				arr[c]=tmp.sum-parent[tmp.sum][tmp.modulo][0];
				c++;
				tm=parent[tmp.sum][tmp.modulo][1];
				tmp.sum=parent[tmp.sum][tmp.modulo][0];
				tmp.modulo=tm;
				//tmp={parent[tmp.sum][tmp.modulo][0],parent[tmp.sum][tmp.modulo][1]};
			}
			for(int i=c-1;i>=0;i--)
				s[c-i-1]=arr[i]+'0';
			s[c]='\0';
			printf("%s\n",s);
		}
	}
	return 0;
}
