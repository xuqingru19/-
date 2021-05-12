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
	//指针初始化！！！ 
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
