//数组
/*
同种类型 
*/ 
//一位数组静态 
#define maxSize 100
ElemType A[maxSize]; //定义时指定数组大小
//一位数组动态
ElemType *A;
A=(ElemType *)malloc(maxSize*sizeof(ElemType));
if(!A) return ERROR;
//一维数组不是线性表，也不是顺序表，或许可以被称为广义表，扩展叫法

//二维数组
typedef T array2[m][n];    //T为元素类型
/*等价于：
    typedef T array1[n];         //列向量类型
    typedef array1 array2[m]; //二维数组类型
*/
//二维数组怎么存储，两种方式（行序和列序，C语言以行序为主序） ，高维以低下标、高下标优先两种 
//其实是在构建数据元素和存储位置之间的映射 
typedef struct{
    ElemType  *base;
    int        dim;
    int       *bounds;     //数组各维的大小bi
    int       *constants; //数组映像函数常量基址ci
} Array;

Status InitArray (Array &a, int dim, …);
Status DestroyArray (Array &A);
Status Value (Array A, ElemType &e, …);
Status Assign (Array &A, ElemType e, ….);

#include  <stdarg.h> //提供va_start, va_arg, va_end，用于存取变长参数表
bool InitArray(Array &A, int dim, …) {
	va_list ap; //ap 存放变长参数表信息的数组
    //若维数dim 和各维长度合法，则构造数组 A, 并返回 OK
    if  ( dim <1 || dim > Max_ARRAY_DIM)  return ERROR;
    A.dim = dim;
    A.bounds = (int *) malloc ( dim * sizeof (int)); 
	if (!A.bounds) exit(OVERFLOW);
	//若各维长度合法，则存入 A.bounds, 并求出 A 的元素总数 elemtotal
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
    // 求映象函数的常数??_??, 并存入 A.constants[i-1], i = 1,…,dim
    A.constants[dim -1]= 1; 
    for(i=dim -2; i>= 0; --i)
        A.constants[i] = A.bounds[i+1] * A.constants[i+1] ;
    return true;
}
 
Status Locate(Array A, va_list ap, int &off) { 
    // 若 ap 指示的各下标值合法，则求出该元素在 A 中相对地址 off
    off = 0;
    for ( i=0; i < A.dim; ++i) {
        ind = va_arg(ap,int) ;
        if ( ind < 0 || ind >= A.bounds[i] ) return OVERFLOW;
        off += A.constants[i] * ind;
    }
    return OK;
}

//取值函数 
Status Value(Array A, ElemType &e, …) {
    // 若各下标不超界，则 e 赋值为所指定的 A 的元素值，并返回OK
    va_start(ap, e);
    if ( ( results = Locate(A, ap, off) ) <= 0 ) return result;
    e = * ( A.base + off );
    return OK;
}

//特殊矩阵，压缩空间存储 
//toeplitz矩阵 其任何一条对角线的元素取相同值
//实际场景，矩阵补全问题，

//对称矩阵
//行序优先压缩存储·下·三角矩阵 数组索引方式: k=(i×(i+1))/2+j, i≥j; k=(j×(j+1))/2+i, i<j

//三对角矩阵

//稀疏矩阵 假设 m 行 n 列的矩阵含 t 个非零元素 稀疏因子为δ=t/(m×n)

//三元组顺序表/有序的双下标法 
#define  MAXSIZE  12500
typedef struct {
    int  i, j;            //该非零元的行下标和列下标
    ElemType  e; // 该非零元的值
} Triple; // 三元组类型

typedef  struct {
    Triple  data[MAXSIZE + 1]; 
    int      mu, nu, tu; 
    //矩阵的行数、列数和非零元素个数
} TSMatrix;  // 稀疏矩阵类型

//非零元在表中按行序有序存储
//便于进行依行顺序处理的矩阵运算

Status TransposeMatrix(TSMarix M, TSMatrix &T) {
	//求M矩阵的转置，结果由T返回
	T.mu = M.nu;   T.nu = M.mu; //矩阵的行数、列数互换 
	T.tu = M.tu
	if (T.tu) {				
	    q =0;//转置矩阵的元素号
	    for (col = 0; col < M.nu; col++)    //以转置矩阵的行序为先
	      	for (p = 0; p < M.tu; p++) 		
	            if (M.data[p].j== col) {		
		        	T.data[q].i = M.data[p].j; T.data[q].j = M.data[p].i;
	                T.data[q].e = M.data[p].e;
	 	          	q++;
				}
	}	
	return OK;
}

//快速转置
//num[col]：记录矩阵转置前各列(即转置矩阵各行)非零元素个数
//cpot[col]：记录各列非零元素在转置三元组表中开始存放位置

Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T){
    T.mu = M.nu;  T.nu = M.mu;  T.tu = M.tu;
    if (T.tu) {
        for (col=0; col<M.nu; ++col)  num[col] = 0;
        for (t=0; t<M.tu; ++t)  ++num[M.data[t].j];//!!!
        cpot[0] = 0;
        for (col=1; col<M.nu; ++col)
            cpot[col] = cpot[col-1] + num[col-1];
        for (p=0; p<M.tu; ++p) {
            col = M.data[p].j;    q = cpot[col]; //找该元素在T中的位置
            T.data[q].i = M.data[p].j; T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;      ++cpot[col];
        }
     } // if
    return OK;
} 

//行逻辑联接的顺序表：修改前述的稀疏矩阵的结构定义，增加一个数据成员rpos，指示各行第一个非零元素的位置
#define  MAXMN  500  
typedef struct {
    Triple  data[MAXSIZE + 1]; 
    int     rpos[MAXMN + 1]; //各行第一个非零元的位置表
    int     mu, nu, tu;              
} RLSMatrix;

ElemType Value(RLSMatrix M, int r, int c) {
    //给定行和列坐标(r, c)，求取矩阵元素的值
    p = M.rpos[r]; 
    while(M.data[p].i==r && M.data[p].j < c) 
        p++;
    if(M.data[p].i==r && M.data[p].j==c)
        return M.data[p].e;
    else return 0;
} 

//矩阵乘法 M*N M中每个非零的元素在N中查看相应位置是否为0
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q) {
    if (M.nu != N.mu) return ERROR;
    Q.mu = M.mu; Q.nu = N.nu; Q.tu = 0; 
    if (M.tu*N.tu != 0) {   // Q是非零矩阵
        for (arow=0; arow<M.mu; ++arow) { // 处理M的每一行
    	} // for a row
    } // if    
    return OK;
}

ctemp[    ] = 0;                 // 当前行各元素累加器清零
Q.rpos[arow] = Q.tu+1;      
for (p=M.rpos[arow]; p<M.rpos[arow+1];++p) {
    //对当前行中每一个非零元
    brow=M.data[p].j;          
    if (brow < N.mu)  t = N.rpos[brow+1];
    else  { t = N.tu+1; }
    for (q=N.rpos[brow];  q< t;  ++q) { 
        ccol = N.data[q].j;    // 乘积元素在Q中列号
        ctemp[ccol] += M.data[p].e * N.data[q].e;
    } // for q, 计算Q中第arow行的积并存入ctemp[]
} // 求得Q中第crow( =arow)行的非零元
	for(ccol=0; ccol<Q.nu; ++ccol) //将ctemp[]中非零元素压缩存储到Qdata
	    if (ctemp[ccol]) {
		    if (++Q.tu > MAXSIZE) return ERROR;
		    Q.data[Q.tu] = {arow, ccol, ctemp[ccol]};
	    }
		
//十字链表 链式存储结构
typedef struct OLNode{
	int                         i, j;
	ElemType         e;
      	struct OLNODE  *right, *down;
} OLNode, *Olink;

typedef struct{
	//行和列链表 头指针向量的基址
	Olink   *rhead, *chead;
	in mu, nu, tu;
} CrossList

//基于十字链表创建矩阵
Status CreatSMatrix_OL(CrossList &M) {
   if (M)  Free(M);
   scanf(&m, &n, &t);    M.mu =m;      M.nu=n;      M.tu=t;
   if (!(M.rhead=(Olink *)malloc((m+1)*sizeof(OLink))))   exit(OVERFLOW);
   if ((!(M.chead=(Olink *)malloc((n+1)*sizeof(OLink))))   exit(OVERFLOW);
   Mrhead[ ] = M.chead[ ] = NULL;
   for (scanf(&i, &j, &e); i!=0; scanf(&i, &j, &e)) {
          if ((p=(OLNode *)malloc(sizeof(OLNode))))  exit(OVERFLOW);
          p->i=i; p->j=j; p->e=e; //生成OLNode结点
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
 
 
 
