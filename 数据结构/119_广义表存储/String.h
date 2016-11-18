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
