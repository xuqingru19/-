//����
/*
ͬ������ 
*/ 
//һλ���龲̬ 
#define maxSize 100
ElemType A[maxSize]; //����ʱָ�������С
//һλ���鶯̬
ElemType *A;
A=(ElemType *)malloc(maxSize*sizeof(ElemType));
if(!A) return ERROR;
//һά���鲻�����Ա�Ҳ����˳���������Ա���Ϊ�������չ�з�

//��ά����
typedef T array2[m][n];    //TΪԪ������
/*�ȼ��ڣ�
    typedef T array1[n];         //����������
    typedef array1 array2[m]; //��ά��������
*/
//��ά������ô�洢�����ַ�ʽ�����������C����������Ϊ���� ����ά�Ե��±ꡢ���±��������� 
//��ʵ���ڹ�������Ԫ�غʹ洢λ��֮���ӳ�� 
typedef struct{
    ElemType  *base;
    int        dim;
    int       *bounds;     //�����ά�Ĵ�Сbi
    int       *constants; //����ӳ����������ַci
} Array;

Status InitArray (Array &a, int dim, ��);
Status DestroyArray (Array &A);
Status Value (Array A, ElemType &e, ��);
Status Assign (Array &A, ElemType e, ��.);

#include  <stdarg.h> //�ṩva_start, va_arg, va_end�����ڴ�ȡ�䳤������
bool InitArray(Array &A, int dim, ��) {
	va_list ap; //ap ��ű䳤��������Ϣ������
    //��ά��dim �͸�ά���ȺϷ����������� A, ������ OK
    if  ( dim <1 || dim > Max_ARRAY_DIM)  return ERROR;
    A.dim = dim;
    A.bounds = (int *) malloc ( dim * sizeof (int)); 
	if (!A.bounds) exit(OVERFLOW);
	//����ά���ȺϷ�������� A.bounds, ����� A ��Ԫ������ elemtotal
    elemtotal = 1;
    
	va_start(ap, dim);   
    for ( i=0; i< dim; ++i) {
        A.bounds[i]= va_arg(ap, int) ;
        if (A.bounds[i] <= 0) return false;//UNDERFLOW
        elemtotal *= A.bounds[i]; }
    va_end(ap);
    
	A.base = (ElemType *) malloc(elemtotal * sizeof(ElemType)); 
    if(!A.base)  exit( OVERFLOW);
    
	A.constants=(int *)malloc(dim*sizeof(int)); if  (!A.constants)  exit( OVERFLOW);
    // ��ӳ�����ĳ���??_??, ������ A.constants[i-1], i = 1,��,dim
    A.constants[dim -1]= 1; 
    for(i=dim -2; i>= 0; --i)
        A.constants[i] = A.bounds[i+1] * A.constants[i+1] ;
    return true;
}
 
Status Locate(Array A, va_list ap, int &off) { 
    // �� ap ָʾ�ĸ��±�ֵ�Ϸ����������Ԫ���� A ����Ե�ַ off
    off = 0;
    for ( i=0; i < A.dim; ++i) {
        ind = va_arg(ap,int) ;
        if ( ind < 0 || ind >= A.bounds[i] ) return OVERFLOW;
        off += A.constants[i] * ind;
    }
    return OK;
}

//ȡֵ���� 
Status Value(Array A, ElemType &e, ��) {
    // �����±겻���磬�� e ��ֵΪ��ָ���� A ��Ԫ��ֵ��������OK
    va_start(ap, e);
    if ( ( results = Locate(A, ap, off) ) <= 0 ) return result;
    e = * ( A.base + off );
    return OK;
}

//�������ѹ���ռ�洢 
//toeplitz���� ���κ�һ���Խ��ߵ�Ԫ��ȡ��ֵͬ
//ʵ�ʳ���������ȫ���⣬

//�Գƾ���
//��������ѹ���洢���¡����Ǿ��� ����������ʽ: k=(i��(i+1))/2+j, i��j; k=(j��(j+1))/2+i, i<j

//���ԽǾ���

//ϡ����� ���� m �� n �еľ��� t ������Ԫ�� ϡ������Ϊ��=t/(m��n)

//��Ԫ��˳���/�����˫�±귨 
#define  MAXSIZE  12500
typedef struct {
    int  i, j;            //�÷���Ԫ�����±�����±�
    ElemType  e; // �÷���Ԫ��ֵ
} Triple; // ��Ԫ������

typedef  struct {
    Triple  data[MAXSIZE + 1]; 
    int      mu, nu, tu; 
    //����������������ͷ���Ԫ�ظ���
} TSMatrix;  // ϡ���������

//����Ԫ�ڱ��а���������洢
//���ڽ�������˳����ľ�������

Status TransposeMatrix(TSMarix M, TSMatrix &T) {
	//��M�����ת�ã������T����
	T.mu = M.nu;   T.nu = M.mu; //������������������� 
	T.tu = M.tu
	if (T.tu) {				
	    q =0;//ת�þ����Ԫ�غ�
	    for (col = 0; col < M.nu; col++)    //��ת�þ��������Ϊ��
	      	for (p = 0; p < M.tu; p++) 		
	            if (M.data[p].j== col) {		
		        	T.data[q].i = M.data[p].j; T.data[q].j = M.data[p].i;
	                T.data[q].e = M.data[p].e;
	 	          	q++;
				}
	}	
	return OK;
}

//����ת��
//num[col]����¼����ת��ǰ����(��ת�þ������)����Ԫ�ظ���
//cpot[col]����¼���з���Ԫ����ת����Ԫ����п�ʼ���λ��

Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T){
    T.mu = M.nu;  T.nu = M.mu;  T.tu = M.tu;
    if (T.tu) {
        for (col=0; col<M.nu; ++col)  num[col] = 0;
        for (t=0; t<M.tu; ++t)  ++num[M.data[t].j];//!!!
        cpot[0] = 0;
        for (col=1; col<M.nu; ++col)
            cpot[col] = cpot[col-1] + num[col-1];
        for (p=0; p<M.tu; ++p) {
            col = M.data[p].j;    q = cpot[col]; //�Ҹ�Ԫ����T�е�λ��
            T.data[q].i = M.data[p].j; T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;      ++cpot[col];
        }
     } // if
    return OK;
} 

//���߼����ӵ�˳����޸�ǰ����ϡ�����Ľṹ���壬����һ�����ݳ�Աrpos��ָʾ���е�һ������Ԫ�ص�λ��
#define  MAXMN  500  
typedef struct {
    Triple  data[MAXSIZE + 1]; 
    int     rpos[MAXMN + 1]; //���е�һ������Ԫ��λ�ñ�
    int     mu, nu, tu;              
} RLSMatrix;

ElemType Value(RLSMatrix M, int r, int c) {
    //�����к�������(r, c)����ȡ����Ԫ�ص�ֵ
    p = M.rpos[r]; 
    while(M.data[p].i==r && M.data[p].j < c) 
        p++;
    if(M.data[p].i==r && M.data[p].j==c)
        return M.data[p].e;
    else return 0;
} 

//����˷� M*N M��ÿ�������Ԫ����N�в鿴��Ӧλ���Ƿ�Ϊ0
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q) {
    if (M.nu != N.mu) return ERROR;
    Q.mu = M.mu; Q.nu = N.nu; Q.tu = 0; 
    if (M.tu*N.tu != 0) {   // Q�Ƿ������
        for (arow=0; arow<M.mu; ++arow) { // ����M��ÿһ��
    	} // for a row
    } // if    
    return OK;
}

ctemp[    ] = 0;                 // ��ǰ�и�Ԫ���ۼ�������
Q.rpos[arow] = Q.tu+1;      
for (p=M.rpos[arow]; p<M.rpos[arow+1];++p) {
    //�Ե�ǰ����ÿһ������Ԫ
    brow=M.data[p].j;          
    if (brow < N.mu)  t = N.rpos[brow+1];
    else  { t = N.tu+1; }
    for (q=N.rpos[brow];  q< t;  ++q) { 
        ccol = N.data[q].j;    // �˻�Ԫ����Q���к�
        ctemp[ccol] += M.data[p].e * N.data[q].e;
    } // for q, ����Q�е�arow�еĻ�������ctemp[]
} // ���Q�е�crow( =arow)�еķ���Ԫ
	for(ccol=0; ccol<Q.nu; ++ccol) //��ctemp[]�з���Ԫ��ѹ���洢��Qdata
	    if (ctemp[ccol]) {
		    if (++Q.tu > MAXSIZE) return ERROR;
		    Q.data[Q.tu] = {arow, ccol, ctemp[ccol]};
	    }
		
//ʮ������ ��ʽ�洢�ṹ
typedef struct OLNode{
	int                         i, j;
	ElemType         e;
      	struct OLNODE  *right, *down;
} OLNode, *Olink;

typedef struct{
	//�к������� ͷָ�������Ļ�ַ
	Olink   *rhead, *chead;
	in mu, nu, tu;
} CrossList

//����ʮ������������
Status CreatSMatrix_OL(CrossList &M) {
   if (M)  Free(M);
   scanf(&m, &n, &t);    M.mu =m;      M.nu=n;      M.tu=t;
   if (!(M.rhead=(Olink *)malloc((m+1)*sizeof(OLink))))   exit(OVERFLOW);
   if ((!(M.chead=(Olink *)malloc((n+1)*sizeof(OLink))))   exit(OVERFLOW);
   Mrhead[ ] = M.chead[ ] = NULL;
   for (scanf(&i, &j, &e); i!=0; scanf(&i, &j, &e)) {
          if ((p=(OLNode *)malloc(sizeof(OLNode))))  exit(OVERFLOW);
          p->i=i; p->j=j; p->e=e; //����OLNode���
          if (M.rhead[i] == NULL || M.rhead[i]->j>j){
                       p->right = M.rhead[i]; M.rhead[i] = p;}
           else{   
	    for (q= M.rhead[i]; (q->right) && q->right->j < j; q=q->right) ;
                      p->right = q->right;   q->right = p;
           }
           if (m.chead[j]==NULL || M.chead[j]->i>i){
                       p->down = M.chead[j]; M.chead[kj]=p;}
           else{    for (q=M.chead[j]; (q->down) && q->down->i < i; q=q->down) ;
                       p->down = q->down; q->down = p;
           }  
   }  
}
 
 
 
