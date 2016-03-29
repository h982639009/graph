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
//int distance[N][N];
//广度优先搜索得到的广度优先树是从指定的源节点到所有其他节点的最短路径，因而只需要一维即可
int distance[N];
int parent[N];

void bfs(int i);
void enQueueK(struct MyQueue *q,int k);
void printBFSTree(int start);
void printChildren(struct MyQueue *q, int p);
int main()
{
	bfs(3);
	printBFSTree(3);
	return 0;
}

//从第i个节点开始遍历图（i的取值从0到N-1）
void bfs(int start)
{
	//首先将所有节点都设置成未访问（白色）
	int i,j;
	for(i=0;i<N;i++)
	{
		visited[i]=0;
	}
	//初始化源节点到其他节点之间的距离
	for(i=0;i<N;i++)
	{
		if(i==start){
			//即源节点到自己本身
			distance[i]=0;
		}else{
			//初始情况下，源节点到其他节点距离均为无穷大
			distance[i]=INT_MAX;
		}
	}
	//源节点的父节点设置为NIL（空），用INT_MIN表示
	parent[start]=NIL;
	struct MyQueue *q;
	createQueue(&q,SIZE_OF_QUEUE);//创建一个循环队列
	insert(q,start);//将起始节点入队
	int k;//记录出队元素
	while(!isEmpty(q)){
		delete(q,&k);
		printf("%d ",k);//打印BFS遍历的节点
		//将所有与k相邻的且没有被访问过的元素入队
		enQueueK(q,k);
		visited[k]=2;//访问完毕设置成黑色
	}
	printf("\n");

}

//将所有与k节点相邻且为白色的节点入队，并设置父节点
void enQueueK(struct MyQueue *q,int k){
	int i,j;
	for(i=0;i<N;i++)
	{
		//将所有与k相邻且尚未访问的节点入队
		if(i!=k && matrix[k][i] && !visited[i]){
			insert(q,i);
			parent[i]=k;
			visited[i]=1;
		}
	}
}

void printBFSTree(int start)
{
	//打印BFS优先树,给定指定的起始节点
	printf("%d\n",start );//打印起始节点根节点
	//打印所有以该节点为跟的节点
	//仍然可以借鉴队列来实现
	struct MyQueue *q;
	createQueue(&q,SIZE_OF_QUEUE);
	insert(q,start);//首先将根节点入队
	int k;//记录出队的元素
	while(!isEmpty(q)){
		delete(q,&k);
		printChildren(q,k);//将k的所有孩子节点入队并打印

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