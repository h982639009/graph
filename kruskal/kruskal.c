#include <stdio.h>
#include <limits.h>

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


//用来记录边的结构，对于无向图来说，start和end只标识了边的两个顶点，并不表示方向
struct Edge{
	int start;//起始节点
	int end;//终止节点
	int weight;//权值
};

int kruskal();
void sort(struct Edge * e,int n);
int compare(struct Edge e1,struct Edge e2);
void swap(struct Edge *e1,struct Edge *e2);
void mergeGroup(int *group,int a,int b);
void printGroup(int *group,int n);

void printEdge(struct Edge *edge,int n);
int main(){
	int cost=kruskal();
	printf("%d\n",cost );
}

int kruskal()
{
	//首先统计所有的边数，并按照非递增的顺序排列
	//首先统计共有多少条边，因为是无向图，所有临接矩阵是对称的，因而我们可以只考虑左下矩阵（即i>j)
	int i,j;
	int count=0;
	int cost=0;
	for(i=0;i<N;i++){
		for(j=0;j<i;j++){
			if(matrix[i][j]<INT_MAX){
				++count;
			}
		}
	}
    
    printf("%d \n",count);
	struct Edge edge[count];//边数组
	int current=0;
	//从矩阵中提取边信息
	for(i=0;i<N;i++){
		for(j=0;j<i;j++){
			if(matrix[i][j]<INT_MAX){
				edge[current].start=i;
				edge[current].end=j;
				edge[current].weight=matrix[i][j];
				current++;
			}
		}
	}
	printEdge(edge,count);
	sort(edge,count);//按从小到大排序
	printEdge(edge,count);

	//首先将所有顶点分组，每个顶点均单独为一组
	int group[N];//记录每个顶点所属组别
	for(i=0;i<N;i++){
		group[i]=i;
	}

	int k=0;//记录当前已经选过的边，减少重复判断的次数
	for(i=1;i<N;i++){
		//需要添加N-1条边，即循环N-1次
		for(j=k;j<count;j++){
			//遍历边数组，每次挑选符合要求的边
			if( group[edge[j].start] != group[edge[j].end]){
				//如果边的两个顶点属于两个不同的集合，则可以添加
				cost+=edge[j].weight;//将边加入最小生成树，cost增加
				printf("weight%d cost%d\n",edge[j].weight,cost );
				//合并顶点。
				mergeGroup(group,edge[j].start,edge[j].end);
				//printGroup(group,N);
				k++;
				break;
			}
			k++;
		}

	}
	return cost;

}


void mergeGroup(int *group,int a,int b){
	int group1=group[a];
	int group2=group[b];
	int min=(group[a]<group[b])?group[a]:group[b];//选择较小的group值最为合并后的新group值
	int i;
	for(i=0;i<N;i++){
		//这个条件表达式有问题，想想为什么？
		//if(group[i]==group[a] || group[i]==group[b]){
		if(group[i]==group1 || group[i]==group2){
			group[i]=min;
		}
	}
}


void sort(struct Edge * e,int n){
	int i,j;
	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if(compare(e[j],e[j+1])>0){
				swap(e+j,e+j+1);
			}
		}
	}
}

int compare(struct Edge e1,struct Edge e2){
	return e1.weight-e2.weight;
}

void swap(struct Edge *e1,struct Edge *e2){
	struct Edge temp;
	temp=*e1;
	*e1=*e2;
	*e2=temp;
}


void printEdge(struct Edge *edge,int n)
{
	printf("edge information\n");
	int i;
	for(i=0;i<n;i++){
		printf("%d ",edge[i].weight);
	}
	printf("\n");

}

void printGroup(int *group,int n){
	printf("the group:\n");
	int i;
	for(i=0;i<n;i++){
		printf("%d ",group[i] );
	}
	printf("\n");

}