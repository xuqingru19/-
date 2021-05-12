//��������������ַ���ɵ���������
/*
����һ����������Ա�
��ɴ����ַ��٣��ַ��������Ժܴ󣬶Դ��Ĳ���������Ҹ���
�ڴ��Ļ��������У�ͨ���ԡ��������塱��Ϊ���������ڴ��в����Ӵ��������Ӵ���ɾ���Ӵ����滻�Ӵ�
*/

/*
C����<string.h>�еĴ�������
char *gets(char *str) �� //��stdin�ж�ȡ��
int puts(char *str) �� //��stdout�����
int strlen(char *str); //���ش��ĳ���
char *strcpy(char *dest, char *src); //���ƴ�
char *strcat(char *dest, char *src); //���Ӵ�
int strcmp(char *str1, char *str2); //�Ƚϴ���  s1<s2ʱ���ظ�������ȷ���0��s1>s2ʱ��������
char *strstr(char *str,char *substr); //�����Ӵ��״γ��ֵ�λ��
strchr�������������ַ�c���ַ���s�е�һ�γ��ֵ�λ��
strrchr�������������ַ���s�����һ�γ��ָ����ַ�c��λ��
strspn��������������s1��s2�о��е��ַ�����
strpbrk�����������������ַ������׸���ͬ�ַ���λ��
strupr�����ַ���s�е�Сд��ĸȫ��ת���ɴ�д��ĸ��������ת������ַ���
strlwr�����ַ���s�еĴ�д��ĸȫ��ת����Сд��ĸ��������ת������ַ���
strtol�����ַ���strת���ɳ��������������������
strtod�����ַ���strת����˫�������������������
strdup�����ַ���s���Ƶ��½���λ��
strrev�� ���ַ�������
strtok�����ַ����ָ���ɶ���������һ����Ƭ��
strncat�����ַ���src�����maxlen���ַ����Ƶ��ַ���dest��
strncmp���Ƚ��ַ���s1��s2�е�ǰmaxlen���ַ�
strncpy������src�е�ǰmaxlen���ַ���dest��
stricmp���Բ����ִ�Сд�ķ�ʽ�Ƚ��ַ���s1��s2,������s1-s2
strnicmp���Բ����ִ�Сд�ķ�ʽ�Ƚ��ַ���s1��s2�е�ǰmaxlen���ַ�
*/ 

/*
��ʼ����StrInit
���ٴ�StrDestry
��մ�StrClear
����ֵStrAssign
������StrConcat
ȡ�Ӵ�StrSubstr
�󴮳�StrLen
�д���IsStrEqual
���Ƚ�StrComp
������StrInsert
��ɾ�� StrDelete
������StrCopy
���滻StrReplace
������
���Ƿ�մ�IsStrEmpty
������/��ƥ��StrIndex
*/

//�������򱣴�
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

//˳��/����˳��洢
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1]; 

//��ƴ��
int StrConcat(SString t, SString s1, SString s2){
	int uncut;
	if(s1[0]+s2[0]<=MAXSTRLEN){
		strncpy(&t[1], &s1[1], s1[0]);
		strncpy(&t[s1[0]+1],&s2[1],s2[0]);
		t[0] = s1[0] + s2[0];
		t[t[0]+1] = '\0';
		uncut = true;
	}else if(s1[0]<MAXSTRLEN){
		//s2���ض� 
		strncpy(&t[1], &s1[1], s1[0]);
		strncpy(&t[s1[0]+1],&s2[1],MAXSTRLEN-s1[0]);
	    t[0]=MAXSTRLEN;
		t[MAXSTRLEN+1]='\0';
		uncut=false;
	}else{ //s1[0] >= MAXSTRLEN����s2���ضϣ���ȡs1
	    strncpy(&t[1],&s1[1],MAXSTRLEN);
	    t[0]=MAXSTRLEN;
		t[MAXSTRLEN+1]='\0';
	    uncut=false; 
	}
	return uncut;
} 

//ȡ�Ӵ� ��s�дӵ�pos���ַ���ʼ������len���ַ��ŵ�sub��
bool StrSubStr(SString sub, SString s,int pos,int len) {
 	if(pos<1 || pos>s[0] || len <0 || len > s[0]-pos+1) 
 		return false;
  	strncpy(&sub[1],&s[pos],len);
  	sub[0]= len; 
	sub[sub[0]+1]='\0';
  	return true; 
}

//˳��/�ѷ���洢
typedef struct {
    char *ch;   //���Ƿǿմ����򰴴�����+1����洢��
    int length; //����
    int strsize; //�洢�ռ��С���������Ľ�����
} HString; 

//��ʶ���� 
bool StrInit(HString *s){
	s->ch = (char *)malloc(INITSTRLEN *sizeof(char));
	if(!s->ch) 
		return false;
	s->ch[0]='\0'; 
	s->length = 0; 
	s->strsize= INITSTRLEN; 
	return true;
}

//��ȡ���ĳ��� 
int StrLen(HString *s){
	return s->length;
}

//�Ƚ��������Ƿ���� 
bool IsStrEqual(HString *s1,HString *s2){ int i=0; 
	for(i=0;i<s1->length && i< s2->length; i++)
   		if(s1->ch[i]!= s2->ch[i]) 
			return false;
	if (i<s1->length || i<s2->length) 
		return false;
	else 
		return true;
}

//�Ƚ������� s����t������0��s����t������ֵ����0��sС��t������ֵС��0
int StrComp(HString *s, HString *t){
	for(i=0;i<s->length && i<t->length;i++)
    	if(s->ch[i] !=t->ch[i]) 
			return (s->ch[i]-t->ch[i]);
	return (s->length-t->length);
}

// ���ַ������������ַ�������s
bool StrAssign(HString *s, char *sc){
	int i=0;
	//��sc�Ĵ�����i����β������sc[i]=��\0��
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
	s->ch[i]='\0';  //��ʽ�ز��ϴ�������־
	return true;
}

bool StrConcat(HString *s, HString *s1, HString *s2) {
	// ��s1,s2ƴ�ӳ�s
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
	} //����s1��
	while(i<s1->length+s2->length){ 
		s->ch[i]=s2->ch[i-s1->length]; 
		i++;
	} //����s2��
	s->ch[i]='\0';
	s->length = s1->length + s2->length;
	return true; 
}

// ȡ�Ӵ�����s�дӵ�i���ַ���ʼ������j���ַ��ŵ�subs
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

//��s�ĵ�i���ַ�֮ǰ(1<=i<=s->length+1)�����ַ���t
bool StrInsert(HString *s,int i,HString *t) { 
	int j;
	if(i<=0 || i>s->length+1) return false; // λ�ò��Ϸ�����
	if(s->strsize < s->length + t->length){ //�ռ䲻��
	    s->ch = (char *)realloc(s->ch,
				(s->length+t->length+1)* sizeof(char));
	   if(!s->ch) return false; 
	    s->strsize = s->length + t->length; }
	for(j=s->length-1;j>=i-1;j--) //�ַ����ƣ���Ų�ռ�
	    s->ch[j+t->length] = s->ch[j];
	for(j=0;j<t->length;j++) // ����t
	    s->ch[i+j-1] = t->ch[j];
	s->length += t->length; 
	return true;
}

//���滻����s�ӵ�i���ַ���ʼj�������ַ����ַ���t�滻
bool StrReplace(HString *s, int i, int j, HString *t){
	int k;
	if(i<=0 || i> s->length || j<=0 || j>s->length-i+1) return false;
	if(j<t->length) {
	    if(s->length + t->length-j > s->strsize) {
	        s->ch =(char *) realloc(s->ch,(s->length+t->length-j+1)*sizeof(char));
	        if(!s->ch) return false;
	        s->strsize = s->length + t->length �Cj+1;
	    }
	    for(k=s->length; k>=i+j-1;k--) //����ƣ�Ų�ռ�
	        s->ch[k-j+t->length] = s->ch[k];
	}
	else for(k=i-1+j;k<s->length;k++) s->ch[k-j+t->length] = s->ch[k]; //��ǰ��
	s->length = s->length + t->length -j; s->ch[s->length+1]='\0';
	for(k=0;k<t->length;k++)
	    s->ch[k+i-1] = t->ch[k];
	return true;
}


