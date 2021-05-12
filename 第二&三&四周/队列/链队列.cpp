/*队列的链式表示和实现 
链队列：用链表表示的队列
数据元素结点，设有头结点
队列的队头指针和队尾指针
*/
 
#include <cstdio>
typedef struct Node {
    	ElemType data;
    	struct Node *next;
}QNode;

typedef struct {
	QNode *front;
	QNode *rear;
}LinkedQueue;

//链队列的初识化，构造一个空队列
bool InitQueue(LinkedQueue *lq){
	lq->front = lq->rear = (QNode *)malloc(sizeof(QNode));
	if(!lq->front)
		return false;
	lq->front->next = NULL;
	return true;
} 

//判断队列是否为空 
int IsQueueEmpty(LinkedQueue *lq){
	if(lq->front == lq->rear)
		return 1;
	else 
		return 0;
}

//查看队头元素 
//如果不理解看PPT chapter 3 的第9页 
bool GetFront(LinkedQueue *lq,ElemType *e){
	if(lq->front == lq->rear)
		return false;
	*e = lq->front->next->data;
	return true; 
} 

//元素入队（尾）
bool Enqueue(LinkedQueue *lq, ElemType e){
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	if(!p)
		return false;
	p->data = e;
	p->next = NULL;
	//修改尾指针
	lq->rear->next = p;
	lq->rear = p;
	return true; 
} 

//（队头）元素出队 若队列不空，则删除队列的队头元素；用e返回其值，并返回true；否则返回false
bool Dequeue(LinkedQueue *lq, ElemType *e){
	QNode *p;
	//空队列的话，则出错 
	if(lq->front == lq->rear)
		return false;
	//p指向第一个结点 
	p = lq->front->next; 
	*e = p->data;
	//修改头结点的指针 
	lq->front->next = p->next; 
	//删仅有的一个元素时，需修改尾指针
	if(lq->rear == p)
		lq->rear == lq->front;
	free(p);
	return true; 
} 


