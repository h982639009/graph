#include <stdio.h>
#include <limits.h>
#include <memory.h>

#define N 9
#define SIZE_OF_QUEUE 20
int matrix[N][N]={{0      ,4      ,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,8      ,INT_MAX},
                  {4      ,0      ,8      ,INT_MAX,INT_MAX,INT_MAX,INT_MAX,11     ,INT_MAX},
                  {INT_MAX,8      ,0      ,7      ,INT_MAX,4      ,INT_MAX,INT_MAX,2      },
                  {INT_MAX,INT_MAX,7      ,0      ,9      ,14     ,INT_MAX,INT_MAX,INT_MAX},
                  {INT_MAX,INT_MAX,INT_MAX,9      ,0      ,10     ,INT_MAX,INT_MAX,INT_MAX},
                  {INT_MAX,INT_MAX,4      ,14     ,10     ,0      ,2      ,INT_MAX,INT_MAX},
                  {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,2      ,0      ,1      ,6      },
                  {8      ,11     ,INT_MAX,INT_MAX,INT_MAX,INT_MAX,1      ,0      ,7      },
                  {INT_MAX,INT_MAX,2      ,INT_MAX,INT_MAX,INT_MAX,6      ,7      ,0      }
                 };

int PRIM();
/**PRIM算法实现最小生成树**/
int main(){
	int cost=PRIM();
	printf("%d\n",cost);
	return 0;
}

int PRIM(){
	//distance数组用来记录已经加入最小生成树的顶点集到未加入最小生成树的顶点集的各顶点的最小距离，如果该距离为0，代表该点已经被加入了最小生成树顶点集
	int distance[N];
	int cost=0;//记录总代价
	//囧。。不要滥用memset,memset是将distance的前n个字节的值置为0，而不是前n个元素！
	//memset(distance,1,sizeof(distance));//将distance数组初始化为INT_MAX
	//乖乖使用for循环来将初始化
	int i,j,m;
	for(i=0;i<N;i++){
		distance[i]=INT_MAX;
	}

	//默认初始将第0个顶点加入到最小生成树顶点集中
	distance[0]=0;
	//将第0个顶点加入后，更新distance数组
	for(i=1;i<N;i++){
		if(matrix[0][i]<distance[i]){
			distance[i]=matrix[0][i];
		}
	}

	//每次寻找一条从最小顶点集内部到外部的最轻边，加入到最小生成树中，并归并顶点
	int min=INT_MAX;
	int k=0;
	for(i=1;i<N;i++){
		//共需添加n-1条边，即循环n-1次
		//printf("i:%d\n",i );
		min=INT_MAX;
		for(j=1;j<N;j++){
			//每次循环寻找最轻边
			if(distance[j]>0 && distance[j]<min){
				min=distance[j];
				k=j;
			}
		}
		//选中了顶点k
		cost+=distance[k];
		printf("k:%d,distance:%d,cost:%d\n",k,distance[k],cost );
		distance[k]=0;//将顶点k并入最小生成树集合中
		//将顶点k并入后，再次更新distance数组
		for(m=1;m<N;m++){
			if(distance[m]>0 && matrix[k][m]<distance[m]){
				distance[m]=matrix[k][m];
			}
		}
	}
	return cost;

}