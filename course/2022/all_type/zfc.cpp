#include<stdio.h>
#include<stdlib.h>

#define ok 1
#define error 0
#define overflow -1
#define maxstrlen 255

typedef unsigned char sstring[maxstrlen + 1];//s[0]用来存放长度
typedef int status; 
typedef char elemtype;

status strassign(sstring &s)//生成字符串
{
	int i = 1;
	char ch;
	//printf("请输入字符串：");
	scanf("%c", &ch);
	while (ch != '\n')
	{
		s[i] = ch;
		i++;
		scanf("%c", &ch);
	}
	s[0] = i - 1;
	return ok;
}

status strcopy(sstring &t, sstring s)//有串S复制得串T
{
	if (!s)
		return ok;//s是空串则无法复制
		
// 补充完整 
	int i;
	for (i=0;i<s[0];i++)
	{
		t[i]=s[i];
	}
	return ok;
}

status strprint(sstring s)//遍历字符串
{
	
// 补充完整 
int i;
    for (i=1;i<=s[0];i++)
    {
        printf("%c",s[i]);
    }
	printf("\n");
	return ok;

}

status listempty(sstring s)//判断s是否为空串
{
	if (s[0] == 0)
		return ok;
	else
		return error;
}

void strlength(sstring s)//输出字符串的长度
{
	printf("\n此字符串的长度为:%d\n", s[0]);
}

int strcompare(sstring s, sstring t)//s与t比较大小
{
	if (!t || !s)
		return error;
		
// 补充完整 
	int i,j;
	j=0;
	for(i=1;i<s[0] && i<t[0];i++)
	{
		j++;
		if (s[i] != t[j])
			return (s[i] - t[j]);
	}
	if (s[0] != t[0])
		return s[0] - t[0];
	else
		return 0;
}

status concat(sstring &t, sstring s1, sstring s2)//将串s1和s2连接起来，用t返回
{
	int i;
	if (s1[0] + s2[0] <= maxstrlen + 1)//未截断
	{
		for (i = 1; i <= s1[0]; i++)
			t[i] = s1[i];
		for (i = 1; i <= s2[0]; i++)
			t[i+s1[0]] = s2[i];//此时串s1已经复制好了，所以t从s[0]+1开始
		t[0] = s1[0] + s2[0];//t的长度为s1+s2
		return ok;
	}
	else if (s1[0]<maxstrlen)
	{
		for (i = 1; i <= s1[0]; i++)
			t[i] = s1[i];
		for (i = 1; i <= maxstrlen - s1[0]; i++)
			t[s1[0] + i] = s2[i];
		t[0] = maxstrlen;
		return error;
	}
	else
	{
		for (i = 1; i <= maxstrlen; i++)
			t[i] = s1[i];
		t[0] = maxstrlen;
		return error;
	}
}

status subtring(sstring &sub,sstring s,int pos,int len)//用sub返回串s 的第pos个长度为len的字串
{
	if (pos<1 || pos>s[0] || len<0 || len>s[0] - pos + 1)
		return error;
		
// 补充完整 
	int i;
	for (i=pos;i<=pos+len-1;i++)
	{
		sub[i-pos+1] = s[i];
	}
	sub[0] = len;
	return ok;

}

int index(sstring s, sstring t, int pos)//求串t在s中第一次出现的位置
{
	if (!t || pos<1 || pos>s[0])
		return error;
		
// 补充完整 
	int i,j;
	i = pos;
	j = 1;
	while (i <= s[0] && j <= t[0])
	{
		if (s[i] == t[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > t[0])
		return i-t[0];
	else 
		return 0;
	
}

status clearstr(sstring &s)//置空串
{
	s[0] = 0;
	return ok;
}

status strinser(sstring &s, int pos, sstring t)//在串s的第pos个字符之后插入串t
{
	if (!s || !t || pos<1 || pos>s[0] + 1)
		return error;
	int i,j;

	
	if (s[0] + t[0] <= maxstrlen)
	{
		s[0] += t[0];
		for (i = s[0]; i >= pos; i--)
			s[i+t[0] ] = s[i];//pos的后半部分往后移
		for (i = pos; i<pos+t[0]; i++)
			s[i] = t[i-pos+1];//在pos的位置开始插入t，j控制t的小标
		return ok;
	}
	
	
	else
	{
		for (i = maxstrlen; i >= pos + t[0]; i--)
			s[i] = s[i - t[0]];
		for (i = pos; i<(pos + t[0]) && i <= maxstrlen; i++)
			s[i] = t[i - pos + 1];
		s[0] = maxstrlen;
		return ok;
	}
}


status strdelete(sstring &s, int pos, int len)//从串s中删除第pos个字符起长度为len的字串
{
	if (!s || pos<1 || pos>s[0] - len + 1)
		return error;
	
// 补充完整 
	int i;
	for (i = pos+len;i<=s[0];i++)
	{
		s[i-len] = s[i];
	}
	s[0]-=len;
	return 0;
}

status destorystring(sstring &s)//串s被销毁
{
	free(s);
	return ok;
}

int main()
{
	sstring s,t,s1,s2,sub;
	int i=3,m;
	int pos = 2;
	printf("输入字符串s：");
	strassign(s);
	printf("s:");
	strprint(s);
	strlength(s);
	strcopy(t, s);
	printf("将串s复制到串t\n");
	printf("t:");
	strprint(t);
	printf("输入新的字符串t：");
	strassign(t);
	printf("t:");
	strprint(t);
	m = strcompare(s, t);
	if (m > 0)
		printf("串s大于串t\n");
	else if (m == 0)
		printf("串s和串t相等\n");
	else
		printf("串s小于串t\n");
	printf("将串s和串t链接后的字符串 s1：");
	concat(s1, s, t);
	strprint(s1);
	printf("当pos=5，len=4时s的字串为:");
	subtring(sub, s, 5, 4);
	strprint(sub);
	i = index(s, t,pos);
	if (i == 0)
		printf("串t在串s中不存在\n");
	else
		printf("t在从%d个字符之后在s中出现的的第一个位置是%d\n" ,pos,i);
	printf("在s的第五个位置插入字符串t后,s:");
	strinser(s, 5, t);
	strprint(s);
	printf("在s的第五个位置起删除长度为4的字符串后,s:");
	strdelete(s, 5, 4);
	strprint(s);
	system("pause");
	return 0;
}

