/*˳��ջ  ��̬˳��ջ�����ö�̬һά�������洢ջ
��ν��ָ̬����ջ�Ĵ�С���Ը�����Ҫ����
��base��ʾջ��ָ�룬ջ�׹̶������
ջ�������Ž�ջ����ջ�������仯����top(��Ϊջ��ָ��)ָ�������е���һ�����д洢λ��
��top==base��Ϊջ�յı��
*/
#define INISIZE 100 //ջ�ռ��ʼ������
#define INCREMENTSIZE 10  //ջ�ռ��������

typedef  int  ElemType ;
typedef struct { 
    int top;    // ջ��ָ��  
	ElemType  *base;  // ջ������ʱֵΪNULL     
	int   stacksize ;        // ��ǰ�ѷ���ռ�
}SqStack ;

//����һ����ջs 
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

//ֻ�鿴�����޸�ջ 
bool GetTop(SqStack *s, ElemType *e){
	//ջ�գ����س����־ 
	if(s->top == 0)
		return false; 
	*e = s->base[s->top -1];
	return true; 
}

bool Push(SqStack *s, ElemType e){
	if(s->top >= s->stacksize){
		//��ջ������������INCREMENTSIZE���洢��Ԫ
		s->base = (ElemType *)realloc(s->base, (s->stacksize + INCREMENTSIZE) *sizeof(ElemType));
		if(!s->base)
			return false;
		s->stacksize += INCREMENTSIZE;
	}
	//e��Ϊ�µ�ջ��Ԫ�أ�ջ��Ԫ�ؼ�1
	s->base[s->top++] = e;
	return true; 
}

bool Pop(SqStack *s, ElemType *e){
	if(s->top == 0)
		return false;
	*e = s->base[-- s->top];
	return true;
}
