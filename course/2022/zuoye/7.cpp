#include <stdio.h>

#include <string.h>

#define MAIN_STR_LEN 100 /* 主串的长度 */

#define SUB_STR_LEN 20 /* 子串的长度 */

/*串的赋值函数，要求：

①　函数接口定义为：int MyStrAssign(char * StrTobeAssigned, char * StrInput);

②　输入参数：待赋值字符串变量StrTobeAssigned，字符串的期望值StrInput；

③　输出参数：无；

④　处理规则及返回值：

    将StrTobeAssigned[1]及之后的内容赋值为StrInput的有效内容，StrTobeAssigned[0]赋值为StrInput有效字符的长度，并返回1；

⑤　假设：两个字符串均不为空串；StrInput存放的是一个完成的字符串（不包含长度）。*/

int MyStrAssign(char *StrTobeAssigned, char *StrInput);

/*串替换函数，要求：

①　函数接口定义为：int MyStrReplace(char * MainStr, char * SubStr1, char * SubStr2);

②　输入参数：主串变量MainStr，子串变量SubStr1，SubStr2；

③　输出参数：无；

④　处理规则及返回值：若主串中存在子串，用SubStr2替换主串MainStr中出现的所有与SubStr1相等的不重叠的子串，返回替换的子串个数；否则返回0。

⑤　假设：主串和两个子串均不为空串；MainStr[0]和SubStr1[0]，SubStr2[0]分别存放字符串的长度*/

int MyStrReplace(char *MainStr, char *SubStr1, char *SubStr2);

/*串的比较函数，要求：

①　函数接口定义为：int MyStrCompare(char * Str1,char * Str2);

②　输入参数：待比较的两个字符串变量Str1，Str2；

③　输出参数：无；

④　处理规则及返回值：若S>T,则返回值为1;若S=T,则返回值为0;若S<T,则返回值为-1。

⑤　假设：两个字符串均不为空串；Str1[0]和Str2[0]分别存放的是这两个字符串的长度。*/

int MyStrCompare(char *Str1, char *Str2);

/*求子串位置的函数，要求：

①　函数接口定义为：int MySubStrIndex(char * MainStr, char * SubStr, int pos);

②　输入参数：主串变量MainStr，子串变量SubStr, 查询主串的起始位置pos；

③　输出参数：无；

④　处理规则及返回值：若主串中从pos起之后存在子串，则返回子串在主串中的位置；否则返回0。

⑤　假设：两个字符串均不为空串；MainStr[0]和SubStr[0]分别存放的是这两个字符串的长度。*/

int MySubStrIndex(char *MainStr, char *SubStr, int pos);

/*主串中删除子串，直接提供源代码，不要求学生实现该函数*/

/* 初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */

/* 操作结果: 从串S中删除第pos个字符起长度为len的子串。失败返回-1，成功返回1*/

char MyStrDelete(char *S, int pos, int len);

/*主串的指定位置插入子串，直接提供源代码，不要求学生实现该函数*/

/* 初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */

/* 操作结果: 在串S的第pos个字符之前插入串T。插入失败返回-1，完全插入返回1,部分插入返回0 */

char MyStrInsert(char *S, int pos, char *T);

/*串的比较函数，要求：

①　函数接口定义为：int MyStrCompare(char * Str1,char * Str2);

②　输入参数：待比较的两个字符串变量Str1，Str2；

③　输出参数：无；

④　处理规则及返回值：若S>T,则返回值为1;若S=T,则返回值为0;若S<T,则返回值为-1。

⑤　假设：两个字符串均不为空串；Str1[0]和Str2[0]分别存放的是这两个字符串的长度。*/

int MyStrCompare(char *Str1, char *Str2)

{

    int i;

    int result = 0;

    for (i = 1; (i <= Str1[0]) && (i <= Str2[0]); i++)

    {

        if (Str1[i] > Str2[i])

        {

            result = 1;

            break;
        }

        else if (Str1[i] < Str2[i])

        {

            result = -1;

            break;
        }

        else

        {

            /*两个字符相等，不用处理，继续循环*/
        }
    }

    /*循环结束后判断result是否为0，如果仍为0则说明至少一个字符串已遍历完但未发现差别*/

    if (result == 0)

    {

        /*有一个字符串已遍历完仍没有差别，判断两个字符串的长度（长的大）*/

        if (Str1[0] > Str2[0])

        {

            result = 1;
        }

        else if (Str1[0] < Str2[0])

        {

            result = -1;
        }

        else

        {

            /*长度和内容都一样，返回0（表示一致），也可不处理（保持默认值）*/

            result = 0;
        }
    }

    else

    {

        /*之前已经判断出结果了，不需要再处理*/
    }

    return result;
}

/*求子串位置的函数，要求：

①　函数接口定义为：int MySubStrIndex(char * MainStr, char * SubStr, int pos);

②　输入参数：主串变量MainStr，子串变量SubStr, 查询主串的起始位置pos；

③　输出参数：无；

④　处理规则及返回值：若主串中从pos起之后存在子串，则返回子串在主串中的位置；否则返回0。

⑤　假设：两个字符串均不为空串；MainStr[0]和SubStr[0]分别存放的是这两个字符串的长度。*/

int MySubStrIndex(char *MainStr, char *SubStr, int pos)

{

    int i, j, result;

    /*基本的防护*/

    if ((pos < 0) || (pos > (MainStr[0] - SubStr[0] + 1)))

    {

        result = 0;
    }

    else

    {

        /*主串中剩余的位置足够存放子串，逐位判断*/

        i = pos;

        j = 1;

        while (i <= MainStr[0] && j <= SubStr[0])

        {

            /*需要填写函数实体*/
            if (MainStr[i] == SubStr[j])
            {
                i++;
                j++;
            }
            else
            {
                i = ++pos;
                j = 1;
            }
        }

        /*循环结束后,如果j大于子串的长度，则说明找到了匹配的子串，否则没找到*/

        if (j > SubStr[0])

        {

            /*需要填写函数实体*/
            result = pos;
        }

        else

        {

            result = 0;
        }
    }

    return result;
}

/*主串中删除子串，直接提供源代码，不要求学生实现该函数*/

/* 初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */

/* 操作结果: 从串S中删除第pos个字符起长度为len的子串。失败返回-1，成功返回1*/

char MyStrDelete(char *S, int pos, int len)

{

    int i;

    if (pos < 1 || pos > S[0] - len + 1 || len < 0)

        return -1;

    for (i = pos + len; i <= S[0]; i++)

        S[i - len] = S[i];

    S[0] -= len;

    return 1;
}

/*主串的指定位置插入子串，直接提供源代码，不要求学生实现该函数*/

/* 初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */

/* 操作结果: 在串S的第pos个字符之前插入串T。插入失败返回-1，完全插入返回1,部分插入返回0 */

char MyStrInsert(char *S, int pos, char *T)

{

    int i;

    if (pos < 1 || pos > S[0] + 1)

        return -1;

    if (S[0] + T[0] <= MAIN_STR_LEN)

    { /* 完全插入 */

        for (i = S[0]; i >= pos; i--)

        {

            S[i + T[0]] = S[i];
        }

        for (i = pos; i < pos + T[0]; i++)

        {

            S[i] = T[i - pos + 1];
        }

        S[0] = S[0] + T[0];

        return 1;
    }

    else

    { /* 部分插入 */

        for (i = MAIN_STR_LEN; i <= pos; i--)

        {

            S[i] = S[i - T[0]];
        }

        for (i = pos; i < pos + T[0]; i++)

        {

            S[i] = T[i - pos + 1];
        }

        S[0] = MAIN_STR_LEN;

        return 0;
    }
}

/*

①　创建由n（100）个元素构成的字符串作为主串，以及由两个由m（20）个元素构成的字符串作为子串；

②　接收从键盘输入的3个字符串分别作为主串、子串1和子串2的内容，自动计算各个字符串的长度分别存放到主串、子串1和子串2的第一个元素位置（调用MyStrAssign），打印主串、子串1和子串2的全部内容；

③　比较子串1和子串2的大小（调用MyStrCompare函数），打印比较结果；

④　分别查询子串1和子串2在主串中的位置（调用MySubStrIndex函数），并打印结果；

⑤　将主串中所有不重叠的子串1替换为子串2（调用MyStrReplace函数），打印替换后的主串内容。*/

int main()

{

    /*define 3 strings*/

    char MainStr[MAIN_STR_LEN];

    char SubStr1[SUB_STR_LEN];

    char SubStr2[SUB_STR_LEN];

    int i;

    int compareResult;

    int pos;

    int replaceCounter = 0;

    /*待临时接收输入的3个字符串*/

    char InputBuf[3][MAIN_STR_LEN];

    printf("please input 3 strings as MainStr, SubStr1 and SubStr2\n");

    scanf("%s %s %s", InputBuf[0], InputBuf[1], InputBuf[2]);

    /*assign 3 strings separately*/

    MyStrAssign(MainStr, InputBuf[0]);

    MyStrAssign(SubStr1, InputBuf[1]);

    MyStrAssign(SubStr2, InputBuf[2]);

    /*分别打印三个数组的内容*/

    printf("MainStr=:%d,", MainStr[0]);

    for (i = 1; i <= MainStr[0]; i++)

    {

        printf("%c,", MainStr[i]);
    }

    printf("\n");

    printf("SubStr1=:%d,", SubStr1[0]);

    for (i = 1; i <= SubStr1[0]; i++)

    {

        printf("%c,", SubStr1[i]);
    }

    printf("\n");

    printf("SubStr2=:%d,", SubStr2[0]);

    for (i = 1; i <= SubStr2[0]; i++)

    {

        printf("%c,", SubStr2[i]);
    }

    printf("\n");

    /*比较两个子串的大小，并打印结果*/

    compareResult = MyStrCompare(SubStr1, SubStr2);

    printf("SubStr1 compare with SubStr2 is %d\n", compareResult);

    /*查询子串1在主串中的位置（调用MySubStrIndex函数），并打印结果；*/

    pos = MySubStrIndex(MainStr, SubStr1, 1);

    printf("pos of SubStr1 in MainStr is %d\n", pos);

    /*查询子串2在主串中的位置（调用MySubStrIndex函数），并打印结果；*/

    pos = MySubStrIndex(MainStr, SubStr2, 1);

    printf("pos of SubStr2 in MainStr is %d\n", pos);

    /*将主串中所有不重叠的子串1替换为子串2（调用MyStrReplace函数），打印替换后的主串内容。*/

    replaceCounter = MyStrReplace(MainStr, SubStr1, SubStr2);

    printf("The content of MainStr after %d times of replacing SubStr1 with SubStr2 is:\n%d,", replaceCounter, MainStr[0]);

    for (i = 1; i <= MainStr[0]; i++)

    {

        printf("%c,", MainStr[i]);
    }

    printf("\n");

    return 0;
}

/*串的赋值函数，要求：

①　函数接口定义为：int MyStrAssign(char * StrTobeAssigned, char * StrInput);

②　输入参数：待赋值字符串变量StrTobeAssigned，字符串的期望值StrInput；

③　输出参数：无；

④　处理规则及返回值：

    将StrTobeAssigned[1]及之后的内容赋值为StrInput的有效内容，StrTobeAssigned[0]赋值为StrInput有效字符的长度，并返回1；

⑤　假设：两个字符串均不为空串；StrInput存放的是一个完成的字符串（不包含长度）。*/

int MyStrAssign(char *StrTobeAssigned, char *StrInput)

{

    /*需要填写函数实体*/
    StrTobeAssigned[0] = strlen(StrInput);
    for (int i=1;i<=StrTobeAssigned[0];i++)
    {
        StrTobeAssigned[i] = StrInput[i-1];
    }
    return 1;
}

/*串替换函数，要求：

①　函数接口定义为：int MyStrReplace(char * MainStr, char * SubStr1, char * SubStr2);

②　输入参数：主串变量MainStr，子串变量SubStr1，SubStr2；

③　输出参数：无；

④　处理规则及返回值：若主串中存在子串，用SubStr2替换主串MainStr中出现的所有与SubStr1相等的不重叠的子串，返回替换的子串个数；否则返回0。

⑤　假设：主串和两个子串均不为空串；MainStr[0]和SubStr1[0]，SubStr2[0]分别存放字符串的长度*/

int MyStrReplace(char *MainStr, char *SubStr1, char *SubStr2)

{

    /*需要填写函数实体*/
    int pos,result;
    result = 0;
    pos = 1;
    while(pos = MySubStrIndex(MainStr,SubStr1,pos))
    {   
        result++;
        MyStrDelete(MainStr,pos,SubStr1[0]);
        MyStrInsert(MainStr,pos,SubStr2);
    }
    return result;
}