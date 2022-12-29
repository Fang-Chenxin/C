#include "stdio.h"
#include "malloc.h"
#define Maxsize 20

typedef struct
{
	char *ch; 
	int length;
}HString;

//初始化字符串
int InitString(HString &p)
{
	p.ch=(char *)malloc(Maxsize*sizeof(char));
	if(p.ch==NULL)
	{
		return 0;
	}
	p.length=0;
	return 1;
}

//串赋值，
int StrAssign(HString &S, char cstr[])
{
    //★★★请补全代码
	int i,n;
	i=0;
	while(cstr[i] != '\0')
	{
		S.ch[i]=cstr[i];
		S.length++;
		i++;
	}
	return 1;


}

//对字符串进行一次循环右移，如’’abcde”变为“eabcd”
void change(HString &T)
{
    //★★★请补全代码
	char e;
	int i,n;
	e = T.ch[T.length-1];
	for (i=T.length-1;i>0;i--)
	{
		T.ch[i]=T.ch[i-1];
	}
	T.ch[0] = e;

}


//BF算法
int Index(HString s,HString t,int pos)
{
	//★★★请补全代码
int lens=s.length;
	int lent=t.length;
	int i,j;
	i=pos;
	j=1;
	if(pos<=0 || pos >lens)
	{
		return 0;
	}
	//开始匹配，用BF算法
	while(i<=lens && j<=lent)
	{
		if(s.ch[i-1]==t.ch[j-1])
		{
			i++;
			j++;
		}
		else
		{
			i=i-j+2;
			j=1;
		}
	}
	if(j>lent)
	{
		return i-lent;
	}
	else
		return 0;

	return 0;
}

int main()
{
	int pos=0;
	HString S;
	HString T;
	int i;
	char person[Maxsize];
	char virus[Maxsize];
	InitString(S);
	InitString(T);

	printf("Enter the DNA sequence of the person to be tested:\n");
	gets(person);
	printf("Enter the COVID-19 sequence:\n");
	gets(virus);

	StrAssign(S,person);
	StrAssign(T,virus);
	
	for(i=0;i<T.length;i++)
	{
		change(T);  //将字符串T循环右移一位
		pos=Index(S,T,1);
		if(pos > 0)
		{
			printf("The person is infected with the COVID-19, and the virus is located at the %d position of the DNA \n",pos);
            i= T.length;
		}
		else if(i==T.length-1)
		{
			printf("The person is not infected with COVID-19 \n");
		}
	}
	return 0;
}
