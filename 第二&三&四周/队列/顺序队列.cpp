//˳����У�����һ�������Ĵ洢��Ԫ(һά����) ���δ�ŴӶ�ͷ����β�ĸ���Ԫ��
/*
�ڷǿն������ͷָ��ʼ��ָ���ͷԪ�أ�����βָ��ʼ��ָ���βԪ�ص���һλ��
��ʼ����front=rear=0
�ж���Ϊ�գ�front==rear
�ж�������rear==MAXQUEUESIZE

��ӣ�����Ԫ�ز���rear��ָ��λ�ã�Ȼ��rear��1 
���ӣ�ɾȥfront��ָ��Ԫ�أ�Ȼ��front��1�����ر�ɾԪ��
*/

#define MAXQUEUESIZE   100

typedef struct queue{
ElemType  Queue_array[MAXQUEUESIZE] ;
int  front; // ��ͷָ��
int  rear;  // ��βָ��
int  queueSize;     //���пռ�Ĵ�С
}SqQueue;




