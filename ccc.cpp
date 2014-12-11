#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <functional>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
//#pragma comment(linker, "/STACK:102400000,102400000")
typedef long long ll;
#define INF 1e9
#define MAXN 21
#define maxn 360
#define mod 1000000007
#define eps 1e-7
#define pi 3.1415926535897932384626433
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define scan(n) scanf("%d",&n)
#define scanll(n) scanf("%I64d",&n)
#define scan2(n,m) scanf("%d%d",&n,&m)
#define scans(s) scanf("%s",s);
#define ini(a) memset(a,0,sizeof(a))
#define out(n) printf("%d\n",n)
ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
typedef long long LL;
const int NN=1000010;
const int MM=1000010;

struct G {
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
    freopen("in.txt","r",stdin);
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
