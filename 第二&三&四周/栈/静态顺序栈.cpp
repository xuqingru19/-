/*
静态顺序栈
采用静态一维数组来存储栈
栈底固定不变的，而栈顶则随着进栈和退栈操作变化的
用一个整型变量top(称为栈顶指针)指向当前栈顶位置
用top=0表示栈空的初始状态，每次top指向栈顶元素在数组中的存储位置
若栈的数组有Maxsize个元素，则top=Maxsize-1时栈满
*/

#define  MAX_STACK_SIZE  100  //栈的大小 
typedef  int  ElemType ;
typedef struct {
	ElemType   stack_array[MAX_STACK_SIZE];
   	int  top;
} SqStack;

