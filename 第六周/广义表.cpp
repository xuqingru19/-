//�����

//��ͷ��β������/ͷβ����洢�ṹ 
typedef enum {ATOM, LIST} ElemTag;
typedef struct GLNode {	
    ElemTag tag; // ATOM or LIST
    union { //ԭ�ӽ��ͱ�������ϲ���
        AtomType atom;	          
        struct {struct GLNode *hp, *tp;} ptr; //ptr.hp, ptr.tpָ�����ı�ͷ����β
    }
} *Glist;

//�ӱ������
typedef enum {ATOM, LIST} ElemTag;
typedef struct GLNode {	
    ElemTag tag; // ATOM or LIST
    union { //ԭ�ӽ��ͱ�������ϲ���
        AtomType atom;	          
		struct GLNode *hp;//ָ���ӱ��ָ��
    };
    struct GLNode *tp;
    //ָ��ͬһ����һ����Ԫ�ؽ���ָ��
} *Glist;

//mԪ����ʽ�ı��
typedef struct MPNode {	
    ElemTag  tag; 
    int exp; //ָ����
    union {	//ԭ�ӽ��ͱ�������ϲ���
    	float   coef;   //ϵ����	          
		struct MPNode *hp;
    };
    struct MPNode *tp;//�൱�����������next
} *Mplist;

//����������
InitGList(&L); //�����յĹ����
CreateGList(&L, S); //���ַ������������
DestroyGList(&L);
//���롢ɾ��������
InsertFirst_GL(&L, e); //����e��L�ĵ�һ��Ԫ��
DeleteFirst_GL(&L, &e);
CopyGList(&T, L);//�������L���Ƶ�T
//״̬����
GListLength(L);   GListDepth(L);
GListEmpty(L);   GetHead(L);    GetTail(L);
//����
Traverse_GL(L, Visit());

//���ַ������������
void CreateGList(Glist &L, SString S) {
	if  (!strComp(S,��()��))  L = NULL;  // �����ձ�
	else {
	   // ���ɱ���
	   	if(!(L=(Glist)malloc(sizeof(GLNode)) )) exit(OVERFLOW)
	   	if (StrLen(S)==1){//������ԭ�ӹ����
	      	 L->tag=ATOM, L->atom = S; }
	   	else {
	    	L->tag=List;   p=L��
	       	//��subΪ ��ȥ�� S ������������Ӵ�
	      	StrSubStr(sub, S,2,StrLen(S)-1);  //sub�������һ���Ӵ� 
	    	//Ϊsub������n���Ӵ�����n���ӱ�
	      	do { //�ظ���n���ӱ�
			 	//������ӱ�hsub=?I
			 	Sever(sub, hsub); 
			 	//�����ɴ�hsub����Ĺ����p?ptr.hp
			 	CreateGList(p->ptr.hp, hsub); 
			 	q=p; 
			 	if (!IsStrEmpty(sub) { 
			   		//���µı�Ϊ��
			   		if(!(p=(GLNode*)malloc(sizeof(GLNode)) )) exit(OVERFLOW);
			   		//����һ���ӱ�ı���*(p->ptr.tp) 
			   		p->tag = LIST;    q->ptr.tp=p;
			   	}
			} while (!IsStrEmpty(sub));
			q->ptr.tp = NULL;    // ��βΪ�ձ�

	    } // else
	  }//else
	return OK;
}
Status  Sever(SString &str, SString &hstr) {
//���ǿմ�str�ָ�Ϊ�����֣�hstrΪ��һ������֮ǰ���Ӵ���strΪ֮����Ӵ�
   	n = StrLength(str);   
   	i=0;   k=0; //k:��δ��Ե������Ÿ���
   	do{
        ++i;
        StrSubStr(ch, str, i, 1); //ȡһ���ַ�
        if ( ch==��(�� )  ++k;
        else ( ch==��)�� )   --k;
   	}while ( i<n && (ch!=��,�� || k!=0) );
   	if (i<n){ //�������Ż�����
 		StrSubStr(hstr, str, 1, i-1); 
 		StrSubStr(str, str, i+1, n-i);
   	}
   	else {  
	   StrCopy(hstr, str);   StrClear(str); 
	}
}

//��������
int GlistDepth(Glist L) { //����ָ��L��ָ�Ĺ��������
	if (!L) return 1; 
	if (L->tag == ATOM) return 0; 
	for (max=0, pp=L; pp; 
	    pp=pp->ptr.tp) { //����pp��ptr.hpΪͷָ����ӱ����
	 	dep = GlistDepth(pp->ptr.hp);
	  	if (dep > max) max = dep;
	}
	//�ǿձ������Ǹ�Ԫ����ȵ����ֵ��1
	return max + 1;
}

//���ƹ����
Status CopyGList(Glist &T, Glist L) {
	if (!L) T = NULL;  // ���ƿձ�
	else {
	  	//��������
	  	if ( !(T =(GList)malloc(sizeof(GLNode))))
	        exit(OVERFLOW); 
	  	T->tag = L->tag;
	  	if (L->tag == ATOM) 
	        T->atom = L->atom; //���Ƶ�ԭ��
	 	else {
		    CopyGList (T->ptr.hp, L->ptr.hp);
		    //����L->ptr.hp��T->ptr.hp
		    CopyGList (T->ptr.tp, L->ptr.tp);
		   	//����L->ptr.tp��T->ptr.tp
		   	}
	} // else
	return OK;
} 

//ɾ��������������ֵΪx������Ԫ��
void delete(LinkedList &L, ElemType x) {
 // ɾ����LΪͷָ��Ĵ�ͷ���ĵ�������
 // ����ֵΪx������Ԫ��
  if (L->next) {
     if (L->next->data==x) {
        p=L->next;  L->next=p->next;
        free(p);  delete(L, x);
        }
     else  delete(L->next, x);
  }
} 
/*
���ݽṹ�Ķ�����
(Chapter5)���������ִ洢��ʽ
����Ӧ������ѡ�����ݽṹ
(Chapter2) ����Ӧ�ã�����Ҫ�Ĳ����� �ұ�ͷ��㡢�ұ�β������P����ǰ����㣬���ʣ����ĸ����ݽṹ�ȽϺã�
��ͷ���ĵ�����L
��ͷ����ѭ��������(ͷָ��)L
��βָ��R��ѭ��������
��ͷ����˫��ѭ������L 
���ݽṹѡ���Ȩ�⿼�ǣ������ԺͿ�ά����(ά�����۵ĸߵ�)
(Chapter5)ϡ��������߼����ӵ�˳������rpos���飻�������ת�����õ��ĸ������� num�� cpot
���ݽṹ������ͨ������������
(Chapter2)�������ͷ���
�û�ͼ������˼��
*/ 
