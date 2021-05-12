#include <cstdio>
#include <cstdlib>

#include <iostream>
using namespace std;

#define LIST_INIT_SIZE  100 //线性表初始大小
#define LISTINCREMENT 10 //线性表增量大小
typedef int ElemType; //这里以存整数为例 
typedef int Status;
Status OK=1,ERROR=0;

typedef struct SqList{ 
ElemType * elem; //线性表存储空间的基地址
int length; //线性表当前长度
int listsize; //当前分配的存储容量
		//以sizeof(ElemType)为单位
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

//线性表的初始化
Status InitList_Sq(SqList *L){
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE *sizeof(ElemType));
	//如果是C语言，则是“L->elem = new ElemType[LIST_INIT_SIZE];”
	//存储分配失败
	//if(!L->elem)
		//exit(OVERFLOW);
	//空表长度为0 
	L->length = 0;
	//初识存储容量 
	L->listsize = LIST_INIT_SIZE; 
	return OK; 
} 

// 元素插入，在第i个元素之前插入元素e （i从1开始计数） 
Status ListInsert_Sq(SqList *L,int i,ElemType e) {
	ElemType *p;
	
	//操作执行条件检查
	//i值不合法 
	if(i<1 || i>L->length+1)
		return ERROR;
	if(L->length >= L->listsize){
		//当前存储空间已满，增加容量
		ElemType *newbase = (ElemType *)realloc(L->elem,(L->listsize + LISTINCREMENT) *sizeof(ElemType));
		//存储分配失败 
		if(!newbase)
			return ERROR;
		//新的基地址 
		L->elem = newbase;
		//新的存储容量
		L->listsize += LISTINCREMENT; 
	} 	
	
	//q为插入位置 
	ElemType *q = &(L->elem[i-1]); 
	//插入位置及之后的元素右移
	for(p = &(L->elem[L->length-1]);p>=q;--p)
		*(p+1) = *p;
	//插入e
	*q=e; 
	//表长+1
	L->length ++;
	return OK; 
}


//元素删除，删除线性表的第i个元素（i从1开始计数）
Status ListDelete_Sq(SqList *L, int i, ElemType *e){
	ElemType *p, *q;
	//i值不合法
	if((i<1) || (i > L->length))
		return ERROR; 
	//p为被删除元素的位置 
	p = &(L->elem[i-1]);
	//被删除的元素的值赋给了e
	*e = *p;
	//q为表尾元素的位置 
	q = L->elem + L->length-1; 
	for(++p;p<=q;++p){
		*(p-1) = *p;//元素左移
	} 
	L->length--;
	return OK; 
} 

//L中查找第1个值与e满足compare()的元素的位置
Status LocateElem_Sq(SqList, ElemType e, Status (*compare)(ElemType, ElemType)){
	int i;
	ElemType *p;
	i=1;//i的初值为第一个元素的位置
	p = L->elem; //p的初值是第一个元素的地址
	while(i<=L->length && (*compare)(*p,e)!=0){
		p++;i++;
	} 
	if(i<=L->length)
		return i;
	else
		return 0;
	//在主程序中的调用方式：ElemType i=LocateElem_Sq(L, 100, compare);
}

//compare()函数举例
Status (*compare)(ElemType a, ElemType b)
{
  if (a<b) return -1;
  if (a>b) return 1;
  return 0;
}

//合并两个有序列表成一新的有序列表Lc 
void MergeList_Sq(SqList *La,SqList *Lb,SqList *Lc){
	ElemType *pa,*pb,*pc,*pc_last,*pb_last;
	pa = La->elem; pb = Lb->elem;
	Lc->listsize = Lc->length = La->length + Lb->length;
	pc = Lc->elem = (ElemType*)malloc(Lc->listsize *sizeof(ElemType)); 
	//存储分配失败
	if(!Lc->elem)
		exit(OVERFLOW);
	pa_last = La->elem + La->length -1;
	pb_last = Lb->elem + Lb->length -1;
	//插入元素 
	while(pa <= pa_last)
		*pc++ = *pa++;
	while(pb <= pb_last) 
		*pc++ = *pb++;
}

