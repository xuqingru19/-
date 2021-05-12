/*顺序栈  动态顺序栈：采用动态一维数组来存储栈
所谓动态指的是栈的大小可以根据需要增加
用base表示栈底指针，栈底固定不变的
栈顶则随着进栈和退栈操作而变化，用top(称为栈顶指针)指向数组中的下一个空闲存储位置
用top==base作为栈空的标记
*/
#define INISIZE 100 //栈空间初始分配量
#define INCREMENTSIZE 10  //栈空间分配增量

typedef  int  ElemType ;
typedef struct { 
    int top;    // 栈顶指针  
	ElemType  *base;  // 栈不存在时值为NULL     
	int   stacksize ;        // 当前已分配空间
}SqStack ;

//构造一个空栈s 
bool InitStack(SqStack *s){
	s->base = (ElemType *)malloc(INITSIZT *sizeof(ElemType));
	if(!s)
		return false;
	s->stacksize = INITSIZE;
	s->top = 0; 
	return true;
}

int GetLen(SqStack *s){
	return (s->top);
}

//只查看，不修改栈 
bool GetTop(SqStack *s, ElemType *e){
	//栈空，返回出错标志 
	if(s->top == 0)
		return false; 
	*e = s->base[s->top -1];
	return true; 
}

bool Push(SqStack *s, ElemType e){
	if(s->top >= s->stacksize){
		//若栈已满，则增加INCREMENTSIZE个存储单元
		s->base = (ElemType *)realloc(s->base, (s->stacksize + INCREMENTSIZE) *sizeof(ElemType));
		if(!s->base)
			return false;
		s->stacksize += INCREMENTSIZE;
	}
	//e成为新的栈顶元素，栈顶元素加1
	s->base[s->top++] = e;
	return true; 
}

bool Pop(SqStack *s, ElemType *e){
	if(s->top == 0)
		return false;
	*e = s->base[-- s->top];
	return true;
}
