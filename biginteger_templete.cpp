#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <map>
#include <string>
#include <set>
#include <bitset>
#include <utility>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <fstream>
#include <list>
using  namespace  std;

const  int MAXL = 500;
struct  BigNum
{
    int  num[MAXL];
    int  len;
};

//高精度比较 a > b return 1, a == b return 0; a < b return -1;
int  Comp(BigNum &a, BigNum &b)
{
    int  i;
    if(a.len != b.len) return (a.len > b.len) ? 1 : -1;
    for(i = a.len-1; i >= 0; i--)
        if(a.num[i] != b.num[i]) return  (a.num[i] > b.num[i]) ? 1 : -1;
    return  0;
}

//高精度加法
BigNum  Add(BigNum &a, BigNum &b)
{
    BigNum c;
    int  i, len;
    len = (a.len > b.len) ? a.len : b.len;
    memset(c.num, 0, sizeof(c.num));
    for(i = 0; i < len; i++)
    {
        c.num[i] += (a.num[i]+b.num[i]);
        if(c.num[i] >= 10)
        {
            c.num[i+1]++;
            c.num[i] -= 10;
        }
    }
    if(c.num[len])
        len++;
    c.len = len;
    return  c;
}
//高精度减法,保证a >= b
BigNum Sub(BigNum &a, BigNum &b)
{
    BigNum  c;
    int  i, len;
    len = (a.len > b.len) ? a.len : b.len;
    memset(c.num, 0, sizeof(c.num));
    for(i = 0; i < len; i++)
    {
        c.num[i] += (a.num[i]-b.num[i]);
        if(c.num[i] < 0)
        {
            c.num[i] += 10;
            c.num[i+1]--;
        }
    }
    while(c.num[len] == 0 && len > 1)
        len--;
    c.len = len;
    return  c;
}
//高精度乘以低精度，当b很大时可能会发生溢出int范围,具体情况具体分析
//如果b很大可以考虑把b看成高精度
BigNum Mul1(BigNum &a, int  &b)
{
    BigNum c;
    int  i, len;
    len = a.len;
    memset(c.num, 0, sizeof(c.num));
    //乘以0，直接返回0
    if(b == 0)
    {
        c.len = 1;
        return  c;
    }
    for(i = 0; i < len; i++)
    {
        c.num[i] += (a.num[i]*b);
        if(c.num[i] >= 10)
        {
            c.num[i+1] = c.num[i]/10;
            c.num[i] %= 10;
        }
    }
    while(c.num[len] > 0)
    {
        c.num[len+1] = c.num[len]/10;
        c.num[len++] %= 10;
    }
    c.len = len;
    return  c;
}

//高精度乘以高精度,注意要及时进位，否则肯能会引起溢出,但这样会增加算法的复杂度，
//如果确定不会发生溢出, 可以将里面的while改成if
BigNum  Mul2(BigNum &a, BigNum &b)
{
    int i, j, len = 0;
    BigNum  c;
    memset(c.num, 0, sizeof(c.num));
    for(i = 0; i < a.len; i++)
    {
        for(j = 0; j < b.len; j++)
        {
            c.num[i+j] += (a.num[i]*b.num[j]);
            if(c.num[i+j] >= 10)
            {
                c.num[i+j+1] += c.num[i+j]/10;
                c.num[i+j] %= 10;
            }
        }
    }
    len = a.len+b.len-1;
    while(c.num[len-1] == 0 && len > 1)
        len--;
    if(c.num[len])
        len++;
    c.len = len;
    return  c;
}

//高精度除以低精度,除的结果为c, 余数为f
void Div1(BigNum &a, int &b, BigNum &c, int &f)
{
    int  i, len = a.len;
    memset(c.num, 0, sizeof(c.num));
    f = 0;
    for(i = a.len-1; i >= 0; i--)
    {
        f = f*10+a.num[i];
        c.num[i] = f/b;
        f %= b;
    }
    while(len > 1 && c.num[len-1] == 0)
        len--;
    c.len = len;
}
//高精度*10
void  Mul10(BigNum &a)
{
    int  i, len = a.len;
    for(i = len; i >= 1; i--)
        a.num[i] = a.num[i-1];
    a.num[i] = 0;
    len++;
    //if a == 0
    while(len > 1 && a.num[len-1] == 0)
        len--;
}

//高精度除以高精度，除的结果为c，余数为f
void Div2(BigNum &a, BigNum &b, BigNum &c, BigNum &f)
{
    int  i, len = a.len;
    memset(c.num, 0, sizeof(c.num));
    memset(f.num, 0, sizeof(f.num));
    f.len = 1;
    for(i = len-1;i >= 0;i--)
    {
        Mul10(f);
        //余数每次乘10
        f.num[0] = a.num[i];
        //然后余数加上下一位
        ///利用减法替换除法
        while(Comp(f, b) >= 0)
        {
            f = Sub(f, b);
            c.num[i]++;
        }
    }
    while(len > 1 && c.num[len-1] == 0)
        len--;
    c.len = len;
}
void  print(BigNum &a)   //输出大数
{
    int  i;
    for(i = a.len-1; i >= 0; i--)
        printf("%d", a.num[i]);
    puts("");
}
//将字符串转为大数存在BigNum结构体里面
BigNum ToNum(char *s)
{
    int i, j;
    BigNum  a;
    a.len = strlen(s);
    for(i = 0, j = a.len-1; s[i] != '\0'; i++, j--)
        a.num[i] = s[j]-'0';
    return  a;
}

void Init(BigNum &a, char *s, int &tag)   //将字符串转化为大数
{
    int  i = 0, j = strlen(s);
    if(s[0] == '-')
    {
        j--;
        i++;
        tag *= -1;
    }
    a.len = j;
    for(; s[i] != '\0'; i++, j--)
        a.num[j-1] = s[i]-'0';
}

int main()
{
    BigNum a, b;
    char  s1[100], s2[100];
    while(scanf("%s %s", s1, s2) != EOF)
    {
        int tag = 1;
        Init(a, s1, tag);    //将字符串转化为大数
        Init(b, s2, tag);
        a = Mul2(a, b);
        if(a.len == 1 && a.num[0] == 0)
        {
            puts("0");
        }
        else
        {
            if(tag < 0) putchar('-');
            print(a);   
        }   
    }   
    return 0;   
}
