//循环队列
 #define MAXQUEUESIZE   100
typedef  struct  queue {
ElemType *base;  // 动态分配的存储空间
int  front; // 队头指针，
		 //若队列不空，指向队头元素
int  rear;  // 队尾指针，若队列不空，
		//指向队列尾元素 的下一个位置
} CircularQueue;

//队列初识化，构造一个空循环队列
bool InitQueue(CircularQueue *cq){
	cq->base = (ElemType *)malloc(MAXQUEUESIZE *sizeof(ElemType));
	if(!cq->base)
		return false;
	cq->front = cq->rear = 0;
	return true; 
} 

//返回队列的元素个数，即队列的长度
int GetLen(CircularQueue *cq){
	return ((cq->rear - cq->front + MAXQUEUESIZE) % MAXQUEUESIZE);
} 

//插入元素e为Q的新的队尾元素
bool Enqueue(CircularQueue *cq, ElemType e){
	//队列满 
	if((cq->rear +1)%MAXQUEUESIZE == cq->front)
		return false;
	cq->base[cq->rear] = e;
	cq->rear = (cq->rear +1)%MAXQUEUESIZE;
	return true; 
} 

//若队列不空，则删除Q的队头元素，用e返回其值，并返回true；否则返回false
bool Dequeue(CircularQueue *cq, ElemType *e){
	if(cq->front == cq->rear)
		return false;
	*e = cq->base[cq->front];
	cq->front = (cq->front +1)%MAXQUEUESIZE;
	return true;
} 



