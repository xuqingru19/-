//ѭ������
 #define MAXQUEUESIZE   100
typedef  struct  queue {
ElemType *base;  // ��̬����Ĵ洢�ռ�
int  front; // ��ͷָ�룬
		 //�����в��գ�ָ���ͷԪ��
int  rear;  // ��βָ�룬�����в��գ�
		//ָ�����βԪ�� ����һ��λ��
} CircularQueue;

//���г�ʶ��������һ����ѭ������
bool InitQueue(CircularQueue *cq){
	cq->base = (ElemType *)malloc(MAXQUEUESIZE *sizeof(ElemType));
	if(!cq->base)
		return false;
	cq->front = cq->rear = 0;
	return true; 
} 

//���ض��е�Ԫ�ظ����������еĳ���
int GetLen(CircularQueue *cq){
	return ((cq->rear - cq->front + MAXQUEUESIZE) % MAXQUEUESIZE);
} 

//����Ԫ��eΪQ���µĶ�βԪ��
bool Enqueue(CircularQueue *cq, ElemType e){
	//������ 
	if((cq->rear +1)%MAXQUEUESIZE == cq->front)
		return false;
	cq->base[cq->rear] = e;
	cq->rear = (cq->rear +1)%MAXQUEUESIZE;
	return true; 
} 

//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������true�����򷵻�false
bool Dequeue(CircularQueue *cq, ElemType *e){
	if(cq->front == cq->rear)
		return false;
	*e = cq->base[cq->front];
	cq->front = (cq->front +1)%MAXQUEUESIZE;
	return true;
} 



