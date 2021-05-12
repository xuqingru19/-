#include <cstdio>
#include <cstdlib>

#include <iostream>
using namespace std;

#define LIST_INIT_SIZE  100 //���Ա��ʼ��С
#define LISTINCREMENT 10 //���Ա�������С
typedef int ElemType; //�����Դ�����Ϊ�� 
typedef int Status;
Status OK=1,ERROR=0;

typedef struct SqList{ 
ElemType * elem; //���Ա�洢�ռ�Ļ���ַ
int length; //���Ա�ǰ����
int listsize; //��ǰ����Ĵ洢����
		//��sizeof(ElemType)Ϊ��λ
} *L;
Status InitList_Sq(SqList *L);
Status ListInsert_Sq(SqList *L,int i,ElemType e);
int main(){
	//ָ���ʼ�������� 
	SqList *L = (SqList *)malloc(sizeof(SqList));
	int initial = InitList_Sq(L);
	L->length=5; 
	for(int i=0;i < L->length;i++){
		L->elem[i]=i*5+5;
	}
	int result = ListInsert_Sq(L,5,66);
	for(int i=0;i<L->length;i++){
		printf("%d ",L->elem[i]);
	}
	
} 

//���Ա�ĳ�ʼ��
Status InitList_Sq(SqList *L){
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE *sizeof(ElemType));
	//�����C���ԣ����ǡ�L->elem = new ElemType[LIST_INIT_SIZE];��
	//�洢����ʧ��
	//if(!L->elem)
		//exit(OVERFLOW);
	//�ձ���Ϊ0 
	L->length = 0;
	//��ʶ�洢���� 
	L->listsize = LIST_INIT_SIZE; 
	return OK; 
} 

// Ԫ�ز��룬�ڵ�i��Ԫ��֮ǰ����Ԫ��e ��i��1��ʼ������ 
Status ListInsert_Sq(SqList *L,int i,ElemType e) {
	ElemType *p;
	
	//����ִ���������
	//iֵ���Ϸ� 
	if(i<1 || i>L->length+1)
		return ERROR;
	if(L->length >= L->listsize){
		//��ǰ�洢�ռ���������������
		ElemType *newbase = (ElemType *)realloc(L->elem,(L->listsize + LISTINCREMENT) *sizeof(ElemType));
		//�洢����ʧ�� 
		if(!newbase)
			return ERROR;
		//�µĻ���ַ 
		L->elem = newbase;
		//�µĴ洢����
		L->listsize += LISTINCREMENT; 
	} 	
	
	//qΪ����λ�� 
	ElemType *q = &(L->elem[i-1]); 
	//����λ�ü�֮���Ԫ������
	for(p = &(L->elem[L->length-1]);p>=q;--p)
		*(p+1) = *p;
	//����e
	*q=e; 
	//��+1
	L->length ++;
	return OK; 
}
