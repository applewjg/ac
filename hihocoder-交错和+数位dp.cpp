#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
long long mod=1000000007; 
long long base[20]; 
long long l,r,k,bit[20],bt,yy;

struct node {
	long long s,n;
}dp[22][300];

node dfs(long long pos, long long target, long long limit) {
	node t;
	t.s = t.n = 0;
	if (pos == 0) {
		if (target == 100) t.n = 1;
		return t;
	}
	if ((limit==0)&&(dp[pos][target].n!=-1)) return dp[pos][target];
	long long tail = limit?bit[pos]:9;
	long long sgn = ((yy-pos)%2)?(-1):(1);
	long long head;
	if (pos == yy) head = 1;
	else head = 0;
	for (int i = head; i <= tail; ++i) {
		node tmp = dfs(pos - 1, target-i*sgn, (limit==1)&&(i==bit[pos]));
		if (tmp.n>0) {
			t.n += tmp.n;
			long long p = ((((tmp.n%mod)*base[pos])%mod)*i)%mod;
			t.s +=(tmp.s)%mod;
			t.s = (t.s)%mod;
			t.s += p;
			t.s = (t.s)%mod;
		}
	}
	if (limit==0) dp[pos][target] = t;
	return t;
}
long long cal(long long x,long long y) {
	long long ans=0;     
	if (x==-1) return 0;     
	if (x==0) return 0;     
	bt = 0;     
	while (x) {         
		bt++;         
		bit[bt]=x%10;         
		x/=10;     
	}     
	for (yy=1;yy<=bt;yy++) {         
		memset(dp,-1,sizeof dp);         
		ans+=dfs(yy,y+100,yy==bt).s;//对于每个长度为yy的数字进行处理         
		ans=(ans+mod)%mod;     
	}     
	return ans; 
}
int main() {
	freopen("in.txt","r",stdin);
	base[1] = 1;
	int i = 1;
	while(++i <= 19) {
	    base[i] = (base[i-1]*10)%mod;
	}
	//for (i = 1; i <=19;++i) printf("%d\n", base[i]);
	while(~scanf("%lld%lld%lld",&l,&r,&k)) {         
		printf("%lld\n",(cal(r,k)-cal(l-1,k)+mod)%mod);     
	}
	return 0;
}