//顺序队列：利用一组连续的存储单元(一维数组) 依次存放从队头到队尾的各个元素
/*
在非空队列里，队头指针始终指向队头元素，而队尾指针始终指向队尾元素的下一位置
初始化：front=rear=0
判队列为空：front==rear
判队列满：rear==MAXQUEUESIZE

入队：将新元素插入rear所指的位置，然后rear加1 
出队：删去front所指的元素，然后front加1并返回被删元素
*/

#define MAXQUEUESIZE   100

typedef struct queue{
ElemType  Queue_array[MAXQUEUESIZE] ;
int  front; // 队头指针
int  rear;  // 队尾指针
int  queueSize;     //队列空间的大小
}SqQueue;




