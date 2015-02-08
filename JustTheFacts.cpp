#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXN 10000

int get_last_num(int n)
{
    unsigned m,a,r[]={6,2,4,8};
    m=n;

    for(a=0;m;m/=5)
        a+=(m%5==2)+(m%5==4)*2+m/5;
    return ((n>1)?r[a%4]:1);
}

int f(int n) {
    const int gg[10] = {1,1,2,6,4,4,4,8,4,6};
    if (n <= 1) return 1;
    int g = gg[n%10] * pow(2, 4 - (n/5)%4);
    return f(n/5) * g % 10;
}

int lastdigit(char* buf)
{
    /*
     Lets say D(N) denotes the last non zero digit of factorial, then the algo says
     D(N)=4*D[N/5]*D(Unit digit of N)[If tens digit of N is odd]
     D(N)=6*D[N/5]*D(Unit digit of N)[If tens digit of N is even]; Where [N/5] is greatest Integer Function
     */
    const int mod[20]= {1,1,2,6,4,2,2,4,2,8,4,4,8,4,6,8,8,6,8,2};
        int len=strlen(buf),a[MAXN],i,c,ret=1;
    if (len==1)
        return mod[buf[0]-'0']; //特殊情况当数小于10
    for (i=0; i<len; i++)
        a[i]=buf[len-1-i]-'0';  //字符向数字转换
    for (; len; len-=!a[len-1])
    {
        ret = ret * mod[ a[1]%2*10+a[0] ] % 5;
        for (c=0,i=len-1; i>=0; i--)
        {
            c=c*10+a[i];
            a[i]=c/5;
            c%=5;
        }
    }
    return ret+ret%2*5;
}
int main()
{
    char a[10000];
    while(scanf("%s",a)!=EOF)
    {
        printf("%d\n",lastdigit(a));
    }
    return 0;
}
