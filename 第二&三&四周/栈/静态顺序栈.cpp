/*
��̬˳��ջ
���þ�̬һά�������洢ջ
ջ�׹̶�����ģ���ջ�������Ž�ջ����ջ�����仯��
��һ�����ͱ���top(��Ϊջ��ָ��)ָ��ǰջ��λ��
��top=0��ʾջ�յĳ�ʼ״̬��ÿ��topָ��ջ��Ԫ���������еĴ洢λ��
��ջ��������Maxsize��Ԫ�أ���top=Maxsize-1ʱջ��
*/

#define  MAX_STACK_SIZE  100  //ջ�Ĵ�С 
typedef  int  ElemType ;
typedef struct {
	ElemType   stack_array[MAX_STACK_SIZE];
   	int  top;
} SqStack;

