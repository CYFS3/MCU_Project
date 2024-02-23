#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "stm32f10x.h"                  // Device header

//数据类型
#define ElemType u8
//队列的最大空间
#define MAXSIZE 32
//队列的管理结构
typedef struct Queue
{
	ElemType *base; //指向队列空间的基址
	int       front; //头指针
	int       rear; //尾指针
}Queue;
extern Queue queue;
void QueueInit(void);
void EnQueue(Queue *Q, ElemType x);
ElemType DeQueue(Queue *Q);
int Length(Queue *Q);


#endif
