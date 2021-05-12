/*链式栈*/
typedef struct Node{
    ElemType data;
    struct Node *next;
} LinkedStack;

LinkedStack *InitStack(void);
int GetLen(LinkedStack *s);
Status GetTop(LinkedStack *s,ElemType *e);
Status Push(LinkedStack *s,ElemType e);
Status Pop(LinkedStack *s,ElemType *e);
int IsStackEmpty(LinkedStack *s);

//创建一个带头结点的空栈
LinkedStack *InitStack(void){
	LinkedStack *s;
	s = (LinkedStack *)malloc(sizeof(LinkedStack));
	s->next = NULL;
	return s;
} 

int GetLen(LinkedStack *s){
	int i=0;
	LinkedStack *p;
	p = s->next;
	while(p){
		i++;p=p->next;
	} 
	return i;
}

bool Push(LinkedStack *s, ElemType e){
	LinkedStack *p;
	p = (LinkedStack *)malloc(sizeof(LinkedStack));
	if(!p)
		return false;
	p->data = e;
	//新结点插入到头结点之后 
	p->next = s->next;
	s->next = p;
	return true; 
}

bool Pop(LinkedStack *s, ElemType *e){
	LinkedStack *p;
	if(!s->next)
		return false;
	p = s->next;
	//取栈顶元素 
	*e = p->data;
	//修改栈顶指针 
	s->next = p->next; 
	free(p);
	return true; 
}
