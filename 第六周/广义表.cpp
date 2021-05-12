//广义表

//表头表尾分析法/头尾链表存储结构 
typedef enum {ATOM, LIST} ElemTag;
typedef struct GLNode {	
    ElemTag tag; // ATOM or LIST
    union { //原子结点和表结点的联合部分
        AtomType atom;	          
        struct {struct GLNode *hp, *tp;} ptr; //ptr.hp, ptr.tp指向表结点的表头、表尾
    }
} *Glist;

//子表分析法
typedef enum {ATOM, LIST} ElemTag;
typedef struct GLNode {	
    ElemTag tag; // ATOM or LIST
    union { //原子结点和表结点的联合部分
        AtomType atom;	          
		struct GLNode *hp;//指向子表的指针
    };
    struct GLNode *tp;
    //指向同一层下一个表元素结点的指针
} *Glist;

//m元多项式的表达
typedef struct MPNode {	
    ElemTag  tag; 
    int exp; //指数域
    union {	//原子结点和表结点的联合部分
    	float   coef;   //系数域	          
		struct MPNode *hp;
    };
    struct MPNode *tp;//相当于线性链表的next
} *Mplist;

//创建和销毁
InitGList(&L); //创建空的广义表
CreateGList(&L, S); //由字符串创建广义表
DestroyGList(&L);
//插入、删除、拷贝
InsertFirst_GL(&L, e); //插入e成L的第一个元素
DeleteFirst_GL(&L, &e);
CopyGList(&T, L);//将广义表L复制到T
//状态函数
GListLength(L);   GListDepth(L);
GListEmpty(L);   GetHead(L);    GetTail(L);
//遍历
Traverse_GL(L, Visit());

//由字符串创建广义表
void CreateGList(Glist &L, SString S) {
	if  (!strComp(S,”()”))  L = NULL;  // 创建空表
	else {
	   // 生成表结点
	   	if(!(L=(Glist)malloc(sizeof(GLNode)) )) exit(OVERFLOW)
	   	if (StrLen(S)==1){//建立单原子广义表
	      	 L->tag=ATOM, L->atom = S; }
	   	else {
	    	L->tag=List;   p=L；
	       	//设sub为 脱去串 S 最外层括弧的子串
	      	StrSubStr(sub, S,2,StrLen(S)-1);  //sub里面存了一个子串 
	    	//为sub中所含n个子串建立n个子表
	      	do { //重复建n个子表
			 	//分离出子表串hsub=?I
			 	Sever(sub, hsub); 
			 	//创建由串hsub定义的广义表p?ptr.hp
			 	CreateGList(p->ptr.hp, hsub); 
			 	q=p; 
			 	if (!IsStrEmpty(sub) { 
			   		//余下的表不为空
			   		if(!(p=(GLNode*)malloc(sizeof(GLNode)) )) exit(OVERFLOW);
			   		//建下一个子表的表结点*(p->ptr.tp) 
			   		p->tag = LIST;    q->ptr.tp=p;
			   	}
			} while (!IsStrEmpty(sub));
			q->ptr.tp = NULL;    // 表尾为空表

	    } // else
	  }//else
	return OK;
}
Status  Sever(SString &str, SString &hstr) {
//将非空串str分割为两部分：hstr为第一个逗号之前的子串，str为之后的子串
   	n = StrLength(str);   
   	i=0;   k=0; //k:尚未配对的左括号个数
   	do{
        ++i;
        StrSubStr(ch, str, i, 1); //取一个字符
        if ( ch==‘(’ )  ++k;
        else ( ch==‘)’ )   --k;
   	}while ( i<n && (ch!=‘,’ || k!=0) );
   	if (i<n){ //遇到逗号或括号
 		StrSubStr(hstr, str, 1, i-1); 
 		StrSubStr(str, str, i+1, n-i);
   	}
   	else {  
	   StrCopy(hstr, str);   StrClear(str); 
	}
}

//广义表深度
int GlistDepth(Glist L) { //返回指针L所指的广义表的深度
	if (!L) return 1; 
	if (L->tag == ATOM) return 0; 
	for (max=0, pp=L; pp; 
	    pp=pp->ptr.tp) { //求以pp→ptr.hp为头指针的子表深度
	 	dep = GlistDepth(pp->ptr.hp);
	  	if (dep > max) max = dep;
	}
	//非空表的深度是各元素深度的最大值加1
	return max + 1;
}

//复制广义表
Status CopyGList(Glist &T, Glist L) {
	if (!L) T = NULL;  // 复制空表
	else {
	  	//建立表结点
	  	if ( !(T =(GList)malloc(sizeof(GLNode))))
	        exit(OVERFLOW); 
	  	T->tag = L->tag;
	  	if (L->tag == ATOM) 
	        T->atom = L->atom; //复制单原子
	 	else {
		    CopyGList (T->ptr.hp, L->ptr.hp);
		    //复制L->ptr.hp到T->ptr.hp
		    CopyGList (T->ptr.tp, L->ptr.tp);
		   	//复制L->ptr.tp到T->ptr.tp
		   	}
	} // else
	return OK;
} 

//删除单链表中所有值为x的数据元素
void delete(LinkedList &L, ElemType x) {
 // 删除以L为头指针的带头结点的单链表中
 // 所有值为x的数据元素
  if (L->next) {
     if (L->next->data==x) {
        p=L->next;  L->next=p->next;
        free(p);  delete(L, x);
        }
     else  delete(L->next, x);
  }
} 
/*
数据结构的多样性
(Chapter5)广义表的两种存储方式
根据应用需求，选定数据结构
(Chapter2) 现有应用，其主要的操作是 找表头结点、找表尾结点和找P结点的前驱结点，试问，用哪个数据结构比较好？
带头结点的单链表L
带头结点的循环单链表(头指针)L
带尾指针R的循环单链表
带头结点的双向循环链表L 
数据结构选择的权衡考虑，方便性和可维护性(维护代价的高低)
(Chapter5)稀疏矩阵：行逻辑联接的顺序表加了rpos数组；矩阵快速转置中用到的辅助数组 num和 cpot
数据结构的语义通过操作来体现
(Chapter2)单链表的头结点
用画图来帮助思考
*/ 
