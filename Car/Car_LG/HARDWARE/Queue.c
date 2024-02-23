#include "Queue.h"
#include "stdio.h"


Queue queue;
u8 datap[MAXSIZE];
void QueueInit(void)
{
    queue.base = datap;
    if(queue.base == NULL)return;
	//初始时队列为空，头指针和尾指针都指向0位置
	queue.front = queue.rear = 0;
}

//入队操作
void EnQueue(Queue *Q, ElemType x)
{
	//判断循环队列是否已满
	if(((Q->rear+1)%MAXSIZE) == Q->front)
		return;
	//队列未满，将数据入队
	Q->base[Q->rear] = x;
	//更改尾指针的指向
	Q->rear = (Q->rear+1)%MAXSIZE;
}
//出队操作
ElemType DeQueue(Queue *Q)
{
	
    ElemType res = Q->base[Q->front];
	//如果非空，实现可循环出队
	Q->front = (Q->front+1)%MAXSIZE;
    return res;
}
//获取队列长度（元素个数）
int Length(Queue *Q)
{
	//计算尾指针位置与头指针位置的差距
	int len= Q->rear - Q->front;
	//如果为正数，那么len就是队列的长度；如果为负数，那么MAXSIZE+len才是队列的长度
	len = (len>=0) ? len : MAXSIZE+len;
	return len;
}





