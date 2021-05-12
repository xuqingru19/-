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


//Ԫ��ɾ����ɾ�����Ա�ĵ�i��Ԫ�أ�i��1��ʼ������
Status ListDelete_Sq(SqList *L, int i, ElemType *e){
	ElemType *p, *q;
	//iֵ���Ϸ�
	if((i<1) || (i > L->length))
		return ERROR; 
	//pΪ��ɾ��Ԫ�ص�λ�� 
	p = &(L->elem[i-1]);
	//��ɾ����Ԫ�ص�ֵ������e
	*e = *p;
	//qΪ��βԪ�ص�λ�� 
	q = L->elem + L->length-1; 
	for(++p;p<=q;++p){
		*(p-1) = *p;//Ԫ������
	} 
	L->length--;
	return OK; 
} 

//L�в��ҵ�1��ֵ��e����compare()��Ԫ�ص�λ��
Status LocateElem_Sq(SqList, ElemType e, Status (*compare)(ElemType, ElemType)){
	int i;
	ElemType *p;
	i=1;//i�ĳ�ֵΪ��һ��Ԫ�ص�λ��
	p = L->elem; //p�ĳ�ֵ�ǵ�һ��Ԫ�صĵ�ַ
	while(i<=L->length && (*compare)(*p,e)!=0){
		p++;i++;
	} 
	if(i<=L->length)
		return i;
	else
		return 0;
	//���������еĵ��÷�ʽ��ElemType i=LocateElem_Sq(L, 100, compare);
}

//compare()��������
Status (*compare)(ElemType a, ElemType b)
{
  if (a<b) return -1;
  if (a>b) return 1;
  return 0;
}

//�ϲ����������б��һ�µ������б�Lc 
void MergeList_Sq(SqList *La,SqList *Lb,SqList *Lc){
	ElemType *pa,*pb,*pc,*pc_last,*pb_last;
	pa = La->elem; pb = Lb->elem;
	Lc->listsize = Lc->length = La->length + Lb->length;
	pc = Lc->elem = (ElemType*)malloc(Lc->listsize *sizeof(ElemType)); 
	//�洢����ʧ��
	if(!Lc->elem)
		exit(OVERFLOW);
	pa_last = La->elem + La->length -1;
	pb_last = Lb->elem + Lb->length -1;
	//����Ԫ�� 
	while(pa <= pa_last)
		*pc++ = *pa++;
	while(pb <= pb_last) 
		*pc++ = *pb++;
}

