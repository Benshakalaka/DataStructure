#include <stdio.h>		//可用作头文件
#include <string.h>
#include <malloc.h>

typedef struct
{
	char *c;
	int len;
}HString;

//初始化一个结构体（串）
void StrInit(HString &T)
{
	T.c = NULL;
	T.len = 0;
}

//在串S第pos个字符前插入T
bool StrInsert(HString &S,int pos,HString T)
{
	if(pos<1 || pos>S.len) return false;
	S.c = (char *)realloc(S.c,sizeof(char) * (S.len + T.len+1));
	int i,len;
	len = S.len-pos+1;
	for(i=S.len-1;i>=pos-1;i--)
		S.c[T.len+i]=S.c[i];
	for(i=0;i<T.len;i++)
		S.c[i+pos-1] = T.c[i];
	S.len = S.len + T.len;
	S.c[S.len] = '\0';
	return true;
}

//生成一个其值等于串常量 s　的串 T
void StrAssign(HString &T, char *s)
{
	if(!s) return;
	if(T.c) free(T.c);
	T.len = strlen(s);
	if(T.len == 0)
		T.c = NULL;
	else
	{
		T.c = (char *)malloc(sizeof(char) * T.len + 1);
		strcpy(T.c , s);
	}
}

//返回S的元素个数，称为串的长度
int StrLength(HString S)
{
	return S.len;
}

//若S > T,则返回 >0；若S =T,则返回0；否则返回 <0
int StrCompare(HString S,HString T)
{
	int i;
	for(i=0;S.c[i]&&T.c[i];i++)
		if(S.c[i] != T.c[i]) 
			return S.c[i]-T.c[i];
	return S.len-T.len;
}

//将S清为空串 并释放S所占空间
void ClearString(HString &S)
{
	if(S.c)
	{
		free(S.c);
		S.c = NULL;
	}
	S.len = 0;
}

//用T返回由S1和S2联结而成的新串
void Concat(HString &T,HString S1,HString S2)
{
	if(T.c) free(T.c);
	T.len = S1.len+S2.len;
	T.c = (char *)malloc(sizeof(char) * T.len + 1);
	strcpy(T.c,S1.c);
	strcpy(T.c+S1.len,S2.c);
}

//1<=pos=StrLength(S) 且 0<=len<=Strlength(S)-pos+1
//返回串S的第pos个字符起长度为len的字串
bool SubString(HString &Sub,HString S,int pos,int len)
{
	
	if(pos<1 || pos>S.len || len<1 || len>S.len-pos+1) return false;
	if(Sub.c) free(Sub.c);
	int i;
	Sub.len = len;
	Sub.c = (char *)malloc(sizeof(char) * len+1);
	for(i=0;i<len;i++)
		Sub.c[i] = *(S.c+pos-1+i);
	Sub.c[len] = '\0';
	return true;
}

//输出HString的字符串
void Print(HString &S)
{
	if(!S.c)
		printf("\0");
	else
		printf("%s",S.c);
}
//以上函数都有调试过
int main()
{
	HString X,Y,Z;

	StrInit(X);
	StrInit(Y);
	StrInit(Z);

	char s[]="abcde";
	StrAssign(X,"abcde");
	StrAssign(Y,"fgh");
	StrAssign(Z,"mnxyz");

	StrInsert(X,3,Y);

	Print(X);
	Print(Y);
	Print(Z);
	puts("");

	printf("%s\n",X.c);
	printf("%s\n",Y.c);
	printf("%s\n",Z.c);

	ClearString(X);
	ClearString(Y);
	ClearString(Z);
	return 0;
}