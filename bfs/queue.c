
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//创建用户指定大小的队列，因为采用循环队列，分配的队列空间中有一个元素位置需保留不用，所以在分配时实际分配的大小是size+1
//这样既可保证用户视角可用的空间为size
//返回非负表示创建成功，否则表示创建失败
//参数应该是
int createQueue(struct MyQueue ** queue,int size)
{//size表示队列的大小
	//struct MyQueue queue;//如果是这样编写程序的话，将会返回的是一个局部变量的地址，不太好。
	//可以考虑新增一个参数struct MyQueue *,直接为用户传进来的指针分配地址空间。
	*queue=(struct MyQueue *)malloc(sizeof(struct MyQueue));
	if(*queue==NULL)
	{
		return -1;
	}
	(*queue)->size=size+1;
	(*queue)->queue=(int *)malloc(sizeof(int)*(size+1));
	if((*queue)->queue==NULL)
	{
		return -1;
	}
	(*queue)->front=0;
	(*queue)->rear=0;
	return 0;//
}

//插入元素(将元素e插入到队尾)
//返回值为非负数表示插入成功，否则表示插入失败（队满或q为null）
int insert(struct MyQueue *q,int e){
	if(q==NULL)
	{
		return -1;
	}
	//首先判断是否队满
	if((q->rear+1)%q->size==q->front){
		//队满
		return -1;
	}
	*(q->queue+q->rear)=e;
	//rear不应该是简单加一
	q->rear=(q->rear+1)%q->size;
	return 0;
}

//删除元素（从队首删除元素）
//成功删除返回非负值，否则表示删除失败（队空或q为null）
//e表示删除的元素值
int delete(struct MyQueue *q,int *e){
	if(q==NULL){
		return -1;
	}
	//首先判断是否队空
	if(q->front==q->rear){
		return -1;
	}
	*e=*(q->queue+q->front);
	//front也不是简单加一
	q->front=(q->front+1)%q->size;
	return 0;
}

//返回当前队列中的元素个数
int getCount(struct MyQueue *q){
	if(q==NULL){
		return -1;
	}
	//不是简单地rear-front
	return ((q->rear-q->front)+q->size)%q->size;
}

int isEmpty(struct MyQueue *q)
{
	if(q->front==q->rear)
	{
		return 1;
	}else{
		return 0;
	}
}