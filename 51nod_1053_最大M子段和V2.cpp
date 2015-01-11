/*
#include<stdio.h>
__int64 dp[2][100001];
__int64 a[100001];
__int64 res;
int n,m;
__int64 Max(__int64 x,__int64 y)
{
    if(x>y)return x;
    return y;
}
int main()
{
   
//    freopen("a.txt","r",stdin);
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        int t=1;
        res=0;
        int i,j,k;
        for(i=1;i<=n;i++){dp[0][i]=dp[1][i]=0;scanf("%I64d",&a[i]);}
        for(i=1;i<=m;i++)
        {
            dp[t][i]=dp[1-t][i-1]+a[i];
            __int64 max=dp[1-t][i-1];
            for(j=i+1;j<=n-m+i;j++)
            {
                max=Max(max,dp[1-t][j-1]);
                dp[t][j]=Max(dp[t][j-1],max)+a[j];
            }
            t=1-t;
        }
        t=1-t;
        res=-1111111111111;
        for(j=m;j<=n;j++)if(res<dp[t][j])res=dp[t][j];
        printf("%I64d\n",res);
    }

    return 0;
}
*/
/*
#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
long long c[50010];
long long p[50010];
long long a[50010];
long long solve(int m,int n)
{
    long long max;
    int i, j;
    for(i=0; i<n+1; i++)
        p[i]=0;
    c[0]=0;
    for(i=1; i<=m; ++i)
    {
        max=INT_MIN;
        for(j = i; j <= n-m+i; ++j)
        {
            if(c[j-1]< p[j-1])
                c[j]= p[j-1]+a[j-1];
            else
                c[j]=c[j-1]+a[j-1];
            p[j-1]=max;
            if(max<c[j])
                max=c[j];
        }
        p[j-1]=max;
    }
    return max;
}
int main()
{
    int n,m,i,*d;
    freopen("in.txt", "r",stdin);
    while(cin>>n>>m)
    {
        for(i=0;i<n;++i)
            cin>>a[i];
        cout<<solve(m, n)<<endl;
    }
    return 0;
}*/

