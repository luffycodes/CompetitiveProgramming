#include<stdio.h>
#include<iostream>
#include<vector>
#include<assert.h>
 
using namespace std;
 
#define MAX 1000003
#define N 102
 
int array[MAX];
int given[N][N][N];
int dim, x0, y0, z0;
 
void move()
{
	int i, j, k;
	for(i=x0;i<dim-1;i++)
		given[z0][y0][i] = given[z0][y0][i+1];
	x0 = dim-1;
	for(j=y0;j<dim-1;j++)
		given[z0][j][x0] = given[z0][j+1][x0];
	y0 = dim-1;
	for(k=z0;k<dim-1;k++)
		given[k][y0][x0] = given[k+1][y0][x0];
	z0 = dim-1;
	given[z0][y0][z0] = 0;
	return;
}
 
int swaps()
{
	int ans = 0;
	int x, y, z;
	int n;
	int count=1, pos;
	for(z=0;z<dim;z++)
		for(y=0;y<dim;y++)
			for(x=0;x<dim;x++)
				array[count++] = given[z][y][x];
				
	for(pos = dim*dim*dim-1; pos>=0; pos--)
	{
		while((n = array[pos])!=pos)
		{
			array[pos] = array[n];
			array[n] = n;
			ans++;
		}
	}
	return ans;
}
 
int main()
{
	int x, y, z, t;
	int temp;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d", &dim);
		for(z=0;z<dim;z++)
		{
			for(y=0;y<dim;y++)
			{
				for(x=0;x<dim;x++)
				{
					scanf("%d",&temp);
					given[z][y][x] = temp;
					if(temp==0)
					{
						x0 = x;
						y0 = y;
						z0 = z;
					}
				}
			}
		}
		
		move();		
		if(swaps()%2==0) 
			printf("Puzzle can be solved.\n");
		else 
			printf("Puzzle is unsolvable.\n");
	}
	return 0;
}
