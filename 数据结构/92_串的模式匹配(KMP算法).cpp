/*#include <stdio.h>
#include <string.h>
//求字串定位				//书上的T[0] S[0]我觉得应该是记录字符串长度用的 真正是从T[1] S[1]开始的

// 普通算法  时间复杂度为 O(m+n) 有事可达到O(m*n)
int Index(char *S,char *T,int pos)
{
	int sl = strlen(S),tl = strlen(T);//书上的T[0] S[0]记录字符串长度 而我则不是 是单独记录
	int i,j;
	i = pos;
	j=0;
	while(i<sl && j<tl)
	{
		if(S[i] == T[j]) {i++;j++;}			//如果找到相同的 那j开始计数  如果一直记录到整个T的长度那就退出
		else {i=i-j+1; j=0;}				//否则让j回归0   一直到i变成S的长度为止
	}
	if(j == tl) return i-j+1;				//存在就返回位置 否则0
	else return 0;
}

int main()
{
	char A[] = "acabaabaabcacaabc";
	char B[] = "abaabcac";
	printf("%d\n%d\n",Index_KMP(A,B,0),strstr(A,B)-A); //这里Index 返回位置（不是从0开始） strstr是从0开始计数
	return 0;
}*/



//--------------------------------------------------------------------------------------------------------------------------------
// KMP算法
//			a	b	a	a	b	c	a	c
//模版    ----------------------------------(abaabcac的模版)		理解这个算法的主要核心就是理解这个模版数组	
//      j | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |		这一行可以理解为正好在第j个不匹配 断在第j个(函数中的形参 T 数组)这里 前面是匹配的
//       -----------------------------------
//   next | 0 | 1 | 1 | 2 | 2 | 3 | 1 | 2 |		这一行是上面断在了第j个 需要从第next个开始 重新与(T中)第j个相对应的(S)中i进行比较 若匹配则继续(其实里面有递归存在)
//       ------------------------------------
//那么这个模版是怎么出来的呢？  以abaabcac为例  j=1时，也就是第一个就不跟a匹配(相同) 就令j=0(一开始也不知为何等于0 原来是运用在判断中 下面会讲到) ；j=2时 说明在b处断掉(S中的字母不是b 那可能是a) 但前面a是匹配的 再看前面一小串是 a 那只能结束重新回到a(j=1)进行匹配;j=3 同理;j=4时，断在a，(说明在S中相对位置不是a)  但前面aba是匹配的 前面一小串是aba，接下来比较可以从T中第二个字母开始和S中所断位置进行比较(那个不是a的字母，可能是b，若不是b 那再由next变成0)；j=5同理；j=6时，断在c(S中不是c)，前面一小串abaab是匹配的，c前面两个字母正好是ab 与T中开头相同 ，就从第三个字母开始判断(可能是a呢。。)
#include <stdio.h>									//取自书本p92页 模式匹配改进
#include <string.h>
int Index_KMP(char *S,char *T,int pos)
{
	int sl = S[0]-'0',tl = T[0]-'0';
	int i,j;
	i = pos;
	j=1;
	int k[] ={0,0,1,1,2,2,3,1,2};			//k[0]无意义 为了下标更简明
	while(i<=sl && j<=tl)
	{
		if(j==0 || S[i] == T[j]) {i++;j++;}				//当j==0时候也要i++ ，也要S中向后推一位 因为等于0时候说明从T中开头字母进行比较 第一个字母就不同 那自然就从S中向后推 ；当S[i] == T[j]时向后推 这时是因为字母匹配 当然要一个个继续匹配下去 看是否完全相同 不同就退到next数组中的数
 		else j = k[j];
	}
	return i-tl;
}

int main()
{
	char A[] = "xacabaabaabcacaabc";
	char B[] = "xabaabcac";
	//处理一下字符串
	A[0] = strlen(A)-1+'0';
	B[0] = strlen(B)-1+'0';
	printf("%d\n",Index_KMP(A,B,1));
	return 0;
}