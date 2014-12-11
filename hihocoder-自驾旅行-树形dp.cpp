//#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <cctype>
#include <string>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <map>
#include <set>
using namespace std;
#define MP(x,y) make_pair((x),(y))
#define PB(x) push_back(x)
typedef long long LL;
//typedef unsigned __int64 ULL;
/* ****************** */
const int INF=100011122;
const double INFF=1e100;
const double eps=1e-8;
const int mod=1000000007;
const int NN=1000010;
const int MM=1000010;
/* ****************** */

struct G
{
    int v,w1,w2,next;
}E[NN*2];
int p[NN],T;
bool vis[NN];
LL dp[NN][5];
int si[NN];

void add(int u,int v,int w1,int w2)
{
    E[T].v=v;
    E[T].w1=w1;
    E[T].w2=w2;
    E[T].next=p[u];
    p[u]=T++;
}

void dfs(int u,int fa)
{
    int i,v;
    si[u]=vis[u];

    LL temp=0,t2,t3=0,t41=0;
    LL f1,f2,ff1,ff2;
    int match = -1;
    f1=f2=1LL<<50;

    dp[u][1]=0;
    dp[u][2]=0;
    dp[u][4]=0;
    for(i=p[u];i+1;i=E[i].next)
    {
        v=E[i].v;
        if(v==fa)continue;
        dfs(v,u);
        si[u]+=si[v];
        if(si[v]>0)
        {
            temp=min(temp,dp[v][0]-dp[v][1]-E[i].w1);

            dp[u][1]+=dp[v][1]+E[i].w1*2;

            t2=min(dp[v][1]+E[i].w1*2,dp[v][2]+E[i].w2*2);

            dp[u][2]+=t2;

            t3=min(t3,E[i].w1+E[i].w2+dp[v][3]-t2);

            dp[u][4]+=t2;
            t41=min(t41, min(dp[v][0]+E[i].w1,dp[v][4]+E[i].w2) - t2 );

            ff1=E[i].w1+E[i].w2+dp[v][3]-t2;
            if(ff1<f1)
            {
                match = v;
                f2 = f1;
                f1 = ff1;
            }
            else
                f2=min(f2,ff1);
        }
    }

    dp[u][0]=dp[u][1]+temp;
    dp[u][3]=dp[u][2]+t3;
    dp[u][4]+=t41;
    dp[u][4]=min(dp[u][4],dp[u][3]);

    for(i=p[u];i+1;i=E[i].next)
    {
        v=E[i].v;
        if(v==fa)continue;
        if(si[v]>0)
        {
            t2=min(dp[v][1]+E[i].w1*2,dp[v][2]+E[i].w2*2);
            ff2=E[i].w1+dp[v][0]-t2;
            if(v==match)
                dp[u][4] = min(dp[u][4], dp[u][2] + f2 + ff2);
            else
                dp[u][4] = min(dp[u][4], dp[u][2] + f1 + ff2);
        }
    }
}

int main()
{
    int n,m,i,u,v,w1,w2;
    while(scanf("%d",&n)!=EOF)
    {
        memset(p,-1,sizeof(p));
        T=0;
        memset(vis,false,sizeof(vis));

        for(i=1;i<n;i++)
        {
            scanf("%d%d%d%d",&u,&v,&w1,&w2);
            add(u,v,w1,w2);
            add(v,u,w1,w2);
        }
        scanf("%d",&m);
        for(i=1;i<=m;i++)
        {
            scanf("%d",&u);
            vis[u]=true;
        }

        dfs(1,-1);

        cout<<min(dp[1][0],dp[1][4])<<endl;
    }
    return 0;
}
