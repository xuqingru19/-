//串，由零个或多个字符组成的有限序列
/*
串是一类特殊的线性表
组成串的字符少，字符数量可以很大，对串的操作种类多且复杂
在串的基本操作中，通常以“串的整体”作为操作对象：在串中查找子串、插入子串、删除子串、替换子串
*/

/*
C语言<string.h>中的串处理函数
char *gets(char *str) ； //从stdin中读取串
int puts(char *str) ； //向stdout输出串
int strlen(char *str); //返回串的长度
char *strcpy(char *dest, char *src); //复制串
char *strcat(char *dest, char *src); //联接串
int strcmp(char *str1, char *str2); //比较串，  s1<s2时返回负数，相等返回0，s1>s2时返回正数
char *strstr(char *str,char *substr); //返回子串首次出现的位置
strchr：检索并返回字符c在字符串s中第一次出现的位置
strrchr：检索并返回字符串s中最后一次出现给定字符c的位置
strspn：检索并返回在s1和s2中均有的字符个数
strpbrk：检索并返回两个字符串中首个相同字符的位置
strupr：将字符串s中的小写字母全部转换成大写字母，并返回转换后的字符串
strlwr：将字符串s中的大写字母全部转换成小写字母，并返回转换后的字符串
strtol：将字符串str转换成长整型数，并返回这个数
strtod：将字符串str转换成双精度数，并返回这个数
strdup：将字符串s复制到新建的位置
strrev： 将字符串逆置
strtok：将字符串分割成由定界符隔离的一个个片段
strncat：将字符串src中最多maxlen个字符复制到字符串dest中
strncmp：比较字符串s1与s2中的前maxlen个字符
strncpy：复制src中的前maxlen个字符到dest中
stricmp：以不区分大小写的方式比较字符串s1和s2,并返回s1-s2
strnicmp：以不区分大小写的方式比较字符串s1与s2中的前maxlen个字符
*/ 

/*
初始化串StrInit
销毁串StrDestry
清空串StrClear
串赋值StrAssign
串联接StrConcat
取子串StrSubstr
求串长StrLen
判串等IsStrEqual
串比较StrComp
串插入StrInsert
串删除 StrDelete
串复制StrCopy
串替换StrReplace
引用型
判是否空串IsStrEmpty
串查找/串匹配StrIndex
*/

//将串逆序保存
void StrInvert(char *s){
	char tmp;
	static int i=0;
	int len;
	len = strlen(s);
	if(i<len/2){
		tmp = s[i];
		s[i] = s[len-i-1];
		s[len-i-1] = tmp;
		i++;
		StrInvert(s);
	}
} 

//顺序串/定长顺序存储
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1]; 

//串拼接
int StrConcat(SString t, SString s1, SString s2){
	int uncut;
	if(s1[0]+s2[0]<=MAXSTRLEN){
		strncpy(&t[1], &s1[1], s1[0]);
		strncpy(&t[s1[0]+1],&s2[1],s2[0]);
		t[0] = s1[0] + s2[0];
		t[t[0]+1] = '\0';
		uncut = true;
	}else if(s1[0]<MAXSTRLEN){
		//s2被截断 
		strncpy(&t[1], &s1[1], s1[0]);
		strncpy(&t[s1[0]+1],&s2[1],MAXSTRLEN-s1[0]);
	    t[0]=MAXSTRLEN;
		t[MAXSTRLEN+1]='\0';
		uncut=false;
	}else{ //s1[0] >= MAXSTRLEN，故s2被截断，仅取s1
	    strncpy(&t[1],&s1[1],MAXSTRLEN);
	    t[0]=MAXSTRLEN;
		t[MAXSTRLEN+1]='\0';
	    uncut=false; 
	}
	return uncut;
} 

//取子串 将s中从第pos个字符开始的连续len个字符放到sub中
bool StrSubStr(SString sub, SString s,int pos,int len) {
 	if(pos<1 || pos>s[0] || len <0 || len > s[0]-pos+1) 
 		return false;
  	strncpy(&sub[1],&s[pos],len);
  	sub[0]= len; 
	sub[sub[0]+1]='\0';
  	return true; 
}

//顺序串/堆分配存储
typedef struct {
    char *ch;   //若是非空串，则按串长度+1分配存储区
    int length; //串长
    int strsize; //存储空间大小，包含串的结束符
} HString; 

//初识化串 
bool StrInit(HString *s){
	s->ch = (char *)malloc(INITSTRLEN *sizeof(char));
	if(!s->ch) 
		return false;
	s->ch[0]='\0'; 
	s->length = 0; 
	s->strsize= INITSTRLEN; 
	return true;
}

//获取串的长度 
int StrLen(HString *s){
	return s->length;
}

//比较两个串是否相等 
bool IsStrEqual(HString *s1,HString *s2){ int i=0; 
	for(i=0;i<s1->length && i< s2->length; i++)
   		if(s1->ch[i]!= s2->ch[i]) 
			return false;
	if (i<s1->length || i<s2->length) 
		return false;
	else 
		return true;
}

//比较两个串 s等于t，返回0；s大于t，返回值大于0；s小于t，返回值小于0
int StrComp(HString *s, HString *t){
	for(i=0;i<s->length && i<t->length;i++)
    	if(s->ch[i] !=t->ch[i]) 
			return (s->ch[i]-t->ch[i]);
	return (s->length-t->length);
}

// 将字符串常量赋给字符串变量s
bool StrAssign(HString *s, char *sc){
	int i=0;
	//求sc的串长度i，串尾特征是sc[i]=‘\0’
	while(sc[i]!='\0') 
		i++; 
	if(i>= s->strsize) {
	    s->ch =(char *)realloc(s->ch, (i+1)*sizeof(char));
	    if(!s->ch) 
			return true;
	    s->strsize = i+1; }
	s->length = i;
	for(i=0;i<s->length;i++)
	    s->ch[i] = sc[i];
	s->ch[i]='\0';  //显式地补上串结束标志
	return true;
}

bool StrConcat(HString *s, HString *s1, HString *s2) {
	// 将s1,s2拼接成s
	int i;
	if(s->strsize < (s1->length + s2->length)) {
	    s->ch = (char *)realloc(s->ch, (s1->length+s2->length+1) * sizeof(char));
	    if(!s->ch) 
			return false;
	    s->strsize = s1->length + s2->length+1;
	}
	i=0;
	while(i<s1->length){
		s->ch[i]=s1->ch[i];
		i++;
	} //拷贝s1串
	while(i<s1->length+s2->length){ 
		s->ch[i]=s2->ch[i-s1->length]; 
		i++;
	} //拷贝s2串
	s->ch[i]='\0';
	s->length = s1->length + s2->length;
	return true; 
}

// 取子串，将s中从第i个字符开始的连续j个字符放到subs
bool StrSubstr(HString *subs, HString *s, int i, int j){
	int k;
	if(i<=0 || i> s->length || j<0 || j > s->length -i +1) 
		return false;
	if(subs->strsize < j) {
	    subs->ch =(char *) realloc(subs->ch,(j+1)*sizeof(char));
	    if(!subs->ch) 
			return false;
	    subs->strsize =j+1;
	}
	for(k=0;k<j;k++) 
		subs->ch[k] = s->ch[i-1+k];
	subs->ch[j]='\0';
	subs->length=j;
	return true;
}

//在s的第i个字符之前(1<=i<=s->length+1)插入字符串t
bool StrInsert(HString *s,int i,HString *t) { 
	int j;
	if(i<=0 || i>s->length+1) return false; // 位置不合法出错
	if(s->strsize < s->length + t->length){ //空间不够
	    s->ch = (char *)realloc(s->ch,
				(s->length+t->length+1)* sizeof(char));
	   if(!s->ch) return false; 
	    s->strsize = s->length + t->length; }
	for(j=s->length-1;j>=i-1;j--) //字符后移，腾挪空间
	    s->ch[j+t->length] = s->ch[j];
	for(j=0;j<t->length;j++) // 插入t
	    s->ch[i+j-1] = t->ch[j];
	s->length += t->length; 
	return true;
}

//串替换，将s从第i个字符开始j个连续字符用字符串t替换
bool StrReplace(HString *s, int i, int j, HString *t){
	int k;
	if(i<=0 || i> s->length || j<=0 || j>s->length-i+1) return false;
	if(j<t->length) {
	    if(s->length + t->length-j > s->strsize) {
	        s->ch =(char *) realloc(s->ch,(s->length+t->length-j+1)*sizeof(char));
	        if(!s->ch) return false;
	        s->strsize = s->length + t->length –j+1;
	    }
	    for(k=s->length; k>=i+j-1;k--) //向后移，挪空间
	        s->ch[k-j+t->length] = s->ch[k];
	}
	else for(k=i-1+j;k<s->length;k++) s->ch[k-j+t->length] = s->ch[k]; //向前移
	s->length = s->length + t->length -j; s->ch[s->length+1]='\0';
	for(k=0;k<t->length;k++)
	    s->ch[k+i-1] = t->ch[k];
	return true;
}


