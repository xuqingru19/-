/*���е���ʽ��ʾ��ʵ�� 
�����У��������ʾ�Ķ���
����Ԫ�ؽ�㣬����ͷ���
���еĶ�ͷָ��Ͷ�βָ��
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

//�����еĳ�ʶ��������һ���ն���
bool InitQueue(LinkedQueue *lq){
	lq->front = lq->rear = (QNode *)malloc(sizeof(QNode));
	if(!lq->front)
		return false;
	lq->front->next = NULL;
	return true;
} 

//�ж϶����Ƿ�Ϊ�� 
int IsQueueEmpty(LinkedQueue *lq){
	if(lq->front == lq->rear)
		return 1;
	else 
		return 0;
}

//�鿴��ͷԪ�� 
//�������⿴PPT chapter 3 �ĵ�9ҳ 
bool GetFront(LinkedQueue *lq,ElemType *e){
	if(lq->front == lq->rear)
		return false;
	*e = lq->front->next->data;
	return true; 
} 

//Ԫ����ӣ�β��
bool Enqueue(LinkedQueue *lq, ElemType e){
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	if(!p)
		return false;
	p->data = e;
	p->next = NULL;
	//�޸�βָ��
	lq->rear->next = p;
	lq->rear = p;
	return true; 
} 

//����ͷ��Ԫ�س��� �����в��գ���ɾ�����еĶ�ͷԪ�أ���e������ֵ��������true�����򷵻�false
bool Dequeue(LinkedQueue *lq, ElemType *e){
	QNode *p;
	//�ն��еĻ�������� 
	if(lq->front == lq->rear)
		return false;
	//pָ���һ����� 
	p = lq->front->next; 
	*e = p->data;
	//�޸�ͷ����ָ�� 
	lq->front->next = p->next; 
	//ɾ���е�һ��Ԫ��ʱ�����޸�βָ��
	if(lq->rear == p)
		lq->rear == lq->front;
	free(p);
	return true; 
} 


