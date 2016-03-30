#include <stdio.h>
#include <limits.h>


#define SIZE_OF_QUEUE 20
#define NIL INT_MIN
/*#define N 9
int matrix[N][N]={{0      ,4      ,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,8      ,INT_MAX},
                  {4      ,0      ,8      ,INT_MAX,INT_MAX,INT_MAX,INT_MAX,11     ,INT_MAX},
                  {INT_MAX,8      ,0      ,7      ,INT_MAX,4      ,INT_MAX,INT_MAX,2      },
                  {INT_MAX,INT_MAX,7      ,0      ,9      ,14     ,INT_MAX,INT_MAX,INT_MAX},
                  {INT_MAX,INT_MAX,INT_MAX,9      ,0      ,10     ,INT_MAX,INT_MAX,INT_MAX},
                  {INT_MAX,INT_MAX,4      ,14     ,10     ,0      ,2      ,INT_MAX,INT_MAX},
                  {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,2      ,0      ,1      ,6      },
                  {8      ,11     ,INT_MAX,INT_MAX,INT_MAX,INT_MAX,1      ,0      ,7      },
                  {INT_MAX,INT_MAX,2      ,INT_MAX,INT_MAX,INT_MAX,6      ,7      ,0      }
                 };*/


#define N 5
int matrix[N][N]={{0      ,10     ,INT_MAX,INT_MAX,5      },
                  {INT_MAX,0      ,1      ,INT_MAX,2      },
                  {INT_MAX,INT_MAX,0      ,4      ,INT_MAX},
                  {7      ,INT_MAX,6      ,0      ,INT_MAX},
                  {INT_MAX,3      ,9      ,2      ,0      },
                 };


void print(int * p, int n);
void dijkstra(int s);
void releax(int *added,int *distance,int *pre,int k);
void printPath(int *pre,int end);
int main(){
	printf("please input the number which you want to be the source point:");
	int n;
	scanf("%d",&n);
	dijkstra(n);
	return 0;
}

//s是用户指定的源点
void dijkstra(int s){
	int distance[N];
	int pre[N];//记录前驱节点
	int added[N];//用来记录顶点是否纳入集合

	//首先进行初始化工作
	int i,j;
	for(i=0;i<N;i++){
		distance[i]=INT_MAX;
		pre[i]=NIL;
		added[i]=0;
	}
	//将顶点s添加到集合中，并进行松动操作。
	distance[s]=0;
	added[s]=1;
	releax(added,distance,pre,s);
	//print(distance,N);

	int min,k,m;

	//循环，每次将一个顶点加入集合中，共需要循环N-1次
	for(i=1;i<N;i++){
		//每次挑选一个集合外的distance最小的节点纳入集合
		min=INT_MAX;
		for(j=0;j<N;j++){
			if(!added[j] && distance[j]<min){
				min=distance[j];
				k=j;
			}
		}
		added[k]=1;//将顶点k纳入集合
		//printf("K: %d \n",k);
		//进行松动操作
		releax(added,distance,pre,k);
		//print(distance,N);
	}

	for(i=0;i<N;i++){
		printf("%d -> %d: %d\n",s,i,distance[i] );
		printPath(pre,i);
	}

	print(distance,N);

}

void releax(int *added,int *distance,int *pre,int k){
	int m;
	for(m=0;m<N;m++){
		//这个条件判断有问题，因为我们使用的INT_MAX来初始化的distance，当我们把其再加上一个正数时，将会导致溢出
		//if(!added[m] && distance[m]>distance[k]+matrix[k][m]){
		if(!added[m]){//如果顶点m尚未添加到集合中
			if(distance[m]==INT_MAX){  //如果起始点到m点的距离为无穷大
				if(matrix[k][m]==INT_MAX){
				}else{
					distance[m]=distance[k]+matrix[k][m];
					//如果松动了，需要设置前驱结点
			        pre[m]=k;			
				}
			}else{  //如果起始点到m点的距离不是无穷大
				if(matrix[k][m]==INT_MAX){
				}else if(distance[m]>distance[k]+matrix[k][m]){
					distance[m]=distance[k]+matrix[k][m];
					//如果松动了，需要设置前驱结点
			        pre[m]=k;	
				}
			}
		}
	}
}

//打印从源点s到终点end的路径
void printPath(int *pre,int end)
{
	if(pre[end]==NIL){
		printf("%d <-\n",end );
	}else{
		printf("%d <- ",end);
		printPath(pre,pre[end]);
	}

}
void print(int * p, int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d ",p[i] );
	}
	printf("\n");
}