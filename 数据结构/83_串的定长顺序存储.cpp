#include <stdio.h>					//定长存储也就是存储的字符串的长度是一定的、不可更改的  会出现截断的现象  T[0]存储长度
#include <string.h>
#define MAXSIZE 40							//所谓定长
typedef char String[MAXSIZE+1];				//这样子相当于String是一个字符数组的定义类型


bool StrAssign(String &T,char *chars);				//生成一个其值等于chars的String
void StrCopy(String &T,String S);					//由串S复制得到T
bool StrEmpty(String T);							//判断为空
int StrCompare(String T,String S);					//若T>S返回大于一  T=S返回0   T<S返回小于1
int StrLength(String T);							//求长度
void Concat(String &T,String M,String N);			//T为M，N连接（即M+N）
void SubString(String &T,String S,int pos,int len);	//T为S从第pos个开始后的len个
void ClearString(String &T);						//清零
int Index(String S,String T,int pos);				//若S中存在和T相同的字串，则返回在pos个字符开始第一个相同的位置 不存在就为0						
void Replace(String &T,String S,String V);			//将T中的S换成V
void StrInsert(String &T,int pos,String S);			//在pos位置插入S在T中
void StrDelete(String &T,int pos,int len);			//从pos开始删掉len长度的字符
void PrintString(String &T);						//输出



int main()											//主函数做检测用
{
	String X;
	String Y;
	String Z;


	StrAssign(X,"ssssssssssssssxxxx");				//检测StrAssign函数
	printf("%d\n",StrLength(X));					//检测StrLength函数
	PrintString(X);									//检测PrintString函数


	StrCopy(Y,X);									//检测StrCopy函数
	printf("%d\n",StrLength(Y));
	PrintString(Y);


	StrEmpty(Y);									//检测StrEmpty函数
	StrAssign(Y,"aaaaaaaaaaaaaaaa");
	Concat(Z,X,Y);									//检测Concat函数
	puts("");
	PrintString(Z);

	printf("\n%d\n",StrCompare(X,Y));					//检测StrCompare函数
	printf("%d\n",StrCompare(Y,X));
	printf("%d\n",StrCompare(X,X));

	StrEmpty(Y);StrEmpty(Z);							//检测SubString函数
	StrAssign(Y,"fewrgwfweffwe");	
	puts("");
	SubString(Z,Y,3,4);
	PrintString(Y);	
	PrintString(Z);			


	printf("\n%d\n\n",Index(Y,Z,1));					//检测Index函数

	StrDelete(Y,3,4);									//检测Delete函数
	PrintString(Y);	

	StrInsert(Y,3,X);									//检测StrInsert函数		需考虑几种情况 比如过长
	PrintString(Y);
	printf("%d\n",StrLength(Y));
	StrEmpty(X);
	StrAssign(X,"aaaaaaaaaa");
	StrInsert(Y,3,X);
	PrintString(Y);
	printf("%d\n",StrLength(Y));
	StrEmpty(X);
	StrAssign(X,"aaaaaaaaaa");
	StrInsert(Y,29,X);
	PrintString(Y);
	printf("%d\n",StrLength(Y));
	StrEmpty(X);
	StrAssign(X,"iiiiiiiiii");
	StrInsert(Y,35,X);
	PrintString(Y);
	printf("%d\n\n\n",StrLength(Y));

	


	StrEmpty(X);									//检测Replace函数  主要考虑把整个里面出现的所有替换
	StrEmpty(Y);
	StrEmpty(Z);
	StrAssign(Y,"fewrgwfweffwfwe");
	StrAssign(Z,"fw");
	StrAssign(X,"LLLLI");
	Replace(Y,Z,X);
	PrintString(Y);
	
	
	StrDelete(Y,3,6);										//检测StrDelete函数
	PrintString(Y);
	return 0;
}



bool StrAssign(String &T,char *chars)				//生成一个其值等于chars的String
{
	if(strlen(chars)>MAXSIZE)
		return false;
	T[0] = strlen(chars);
	for(int i=1;i<=T[0];i++)
		T[i] = *(chars+i-1);
	return true;
}

void StrCopy(String &T,String S)					//由串S复制得到T
{
	T[0] = S[0];
	for(int i=1;i<=T[0];i++)
		T[i] = S[i];
}

bool StrEmpty(String T)							//判断为空
{
	if(T[0] == 0)
		return true;
	return false;
}

int StrCompare(String T,String S)					//若T>S返回大于一  T=S返回0   T<S返回小于1
{
	for(int i=1;i<=T[0] && i<=S[0];i++)
		if(T[i]!=S[i])
			return T[i]-S[i];
	return T[0]-S[0];
}

int StrLength(String T)							//求长度
{
	return T[0];
}

void Concat(String &T,String M,String N)			//T为M，N连接（即M+N）
{
	int i;
	if(M[0]+N[0]<=MAXSIZE)
	{
		T[0] = M[0]+N[0];
		for(i=1;i<=M[0];i++)
			T[i] = M[i];
		for(i=1;i<=N[0];i++)
			T[M[0]+i] = N[i];
	}
	else
	{
		T[0] = MAXSIZE;
		for(i=1;i<=M[0];i++)
			T[i] = M[i];
		for(i=1;i<=MAXSIZE-M[0];i++)
			T[M[0]+i] = N[i];
	}
}

void SubString(String &T,String S,int pos,int len)	//T为S从第pos个开始后的len个去掉
{
	if(pos<1 || pos>S[0] || len<0 || len>(S[0]-pos+1))
	{
		printf("Sorry, Wrong Input!\n");
		return;
	}
	int i;
	for(i=1;i<=len;i++)
		T[i] = S[i+pos-1];
	T[0] = len;
}

void ClearString(String &T)						//清零
{
	T[0] = 0;
}

/*这是我自己的  算法明显没有书上的好  
int Index(String S,String T,int pos)				//若S中存在和T相同的字串，则返回在pos个字符开始第一个相同的位置 不存在就为0		
{
	if(pos<1 || pos>S[0])
		return 0;
	int i,j;
	for(i=1;i<=S[0];i++)
	{
		if(S[i]==T[1])
		{
			for(j=1;j<=T[0] && T[i]==S[i+j-1];j++);
			if(j>T[0])
				return i;
		}
	}
	return 0;
}*/	
//也没有明显好 其实差不多	
int Index(String S,String T,int pos)	
{
	if(pos<1 || pos>S[0])
		return 0;
	int i,j;
	i = j = 1;
	while(i<=S[0] && j<=T[0])
	{
		if(S[i]==T[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i-j+2;
			j = 1;
		}
	}
	if(j>T[0])
		return i-j+1;				//j比T[0]大一  所以要加一  当然可以直接减去T[0]
	else
		return 0;
}

//这里既然是插入  那就要考虑是否截断
void StrInsert(String &T,int pos,String S)			//在pos位置插入S在T中
{
	if(pos<1 || pos>T[0])
		return;
	int i;
	/*for(i=T[0]-pos+1;i>0;i--)
		T[i+posS[0]-1] = T[pos+i-1];
	for(i=0;i<S[0];i++)
		T[i+pos] = S[i+1];*/
	if(T[0]+S[0]<=MAXSIZE)
	{
		for(i=T[0];i>=pos;i--)
			T[i+S[0]] = T[i];
		for(i=pos;i<(pos+S[0]);i++)
			T[i] = S[i-pos+1];
		T[0] += S[0]; 
	}
	else
	{
		//int len,j;
		/*len = MAXSIZE-(pos-1+S[0]);
		for(i=MAXSIZE,j=T[0];len>0;len--,i--,j--)
			T[i] = T[j];*/
		for(i=MAXSIZE;i>(pos+S[0]-1);i--)
			T[i] = T[i-S[0]];
		for(i=pos;i<(pos+S[0]) && i<=MAXSIZE;i++)
			T[i] = S[i-pos+1];
		T[0] = MAXSIZE;
	}
}
void Replace(String &T,String S,String V)			//将T中的S换成V
{
	if(StrEmpty(T))
		return;
	int i=1;
	i = Index(T,S,i);
	while(i)							//这里的i可以变为接下去的部分
	{
		StrDelete(T,i,StrLength(S));
		StrInsert(T,i,V);
		i += StrLength(V);
		i = Index(T,S,1);
	}
}

void StrDelete(String &T,int pos,int len)			//从pos开始删掉len长度的字符
{
	if(pos<1 || pos>T[0] || len<0 || len>(T[0]-pos+1))
		return;
	/*自己的
	for(int i=0;i+pos+len<=T[0];i++)
		T[i+pos] = T[i+pos+len];
		*/
	for(int i=pos+len;i<=T[0];i++)
		T[i-len] = T[i];
	T[0] -= len;
}
void PrintString(String &T)						//输出
{
	for(int i=1;i<=T[0];i++)
		printf("%c",T[i]);
	puts("");
}
