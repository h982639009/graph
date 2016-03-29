#include <stdio.h>
#include <limits.h>
#include "queue.h"
//采用临接矩阵的方式保存图
#define N 5
#define SIZE_OF_QUEUE 20
#define NIL INT_MIN
int matrix[N][N]={{0,1,0,1,0},
                  {1,0,1,0,0},
                  {0,1,0,1,1},
                  {1,0,1,0,0},
                  {0,0,1,0,0}
                 };
int visited[N];//访问数组，值为0表示从未访问过（白色），值为1表示访问过但未访问完毕（灰色），值为2表示访问完毕（黑色）
//int distance[N];//深度优先搜索得到的是深度优先树林，无法很快的找到两个节点之间的最短路径，故distance数组没有太大意义
//不过深度优先搜索中经常加盖两个时间戳，分别代表节点变为灰色、黑色的时间点
int parent[N];

void dfs();
void dfs_recursive(int k);
void printForest();
void printTree(int k);
void printChildren(struct MyQueue *q, int p);
int main()
{
	dfs();
	return 0;
}
//不需要用户指定起始节点
void dfs()
{
	//首先进行初始化工作：将所有节点设置为白色（未被发现）
	int i;
	for(i=0;i<N;i++){
		visited[i]=0;//设为白色
		parent[i]=NIL;//父节点设置为空
	}

	for(i=0;i<N;i++){
		if(visited[i]==0){
			//如果为白色节点
			dfs_recursive(i);
		}
	}

	printForest();
}

void dfs_recursive(int k){
	printf("%d ",k);
	visited[k]=1;//设置成灰色
	int i=0;
	for(i=0;i<N;i++){
		if(matrix[k][i]==1 && visited[i]==0){
			parent[i]=k;
			dfs_recursive(i);
		}
	}
	visited[k]=2;//设置成黑色
}

//打印深度优先搜索的深度优先森林
void printForest(){
	int num;//num用来表示森林中树的棵数，（如果一个节点的父节点为空，则该节点为树的根节点，有几个这样的节点，即有几棵树）
	int i;
	for(i=0;i<N;i++){
		if(parent[i]==NIL){
			//打印该节点对应的树
			printf("now print the %dth tree\n", ++num);
			printTree(i);
		}
	}
}

void printTree(int k){
	printf("%d \n",k);//首先打印根节点
	struct MyQueue *queue;
	createQueue(&queue,SIZE_OF_QUEUE);//创建一个队列
	insert(queue,k);
	int element;
	while(!isEmpty(queue)){
		delete(queue,&element);//出队
		printChildren(queue,element);
	}

}

//打印所有的孩子节点
void printChildren(struct MyQueue *q, int p){
	int i;
	for(i=0;i<N;i++){
		if(parent[i]==p){
			insert(q,i);
			printf("%d ",i );
		}
	}
	printf("\n");
}