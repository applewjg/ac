#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
long long mod=1000000007; 
int sum[100010<<2];
int m[100010], ri[100010], t[100010<<2];
void pushup(int root) {
	sum[root] = sum[root<<1] + sum[root<<1|1];
}
void build (int l, int r, int root) {
	if (l == r) {
		scanf("%d%d%d", &sum[root], &m[l], &ri[l]);
		t[l] = 0;
		return;
	}
	int mid = (l+r)>>1;
	build(l,mid, root<<1);
	build(mid+1, r, root<<1|1);
	pushup(root);
}
void recover(int time, int L, int R, int l, int r, int root) {
	if (l==r &&(l>=L && l<=R)) {
		int tmp = (time - t[l])*ri[l];
		if(sum[root] + tmp > m[l]) sum[root] = m[l];
		else sum[root]+=tmp;
		return ;
	}
	int mid = (l+r)>>1;
	if(L<=mid) recover(time, L, R, l, mid, root<<1);
	if(mid<R) recover(time, L, R, mid+1, r, root<<1|1);
	pushup(root);
}
long long query(int L, int R, int l, int r,int root) {
	if(L<=l&&R>=r) return sum[root];
	int mid = (l+r)>>1;
	long long ans = 0;
	if(L<=mid) ans += query(L,R,l,mid,root<<1);
	if(R>mid) ans += query(L,R,mid+1,r,root<<1|1);
	return ans;
}
void clea(int time, int L, int R, int l, int r, int root) {
	if(l==r&&(l>=L && l<=R)){
		t[l] = time;
		sum[root] = 0;
		return;
	}
	int mid = (l+r)>>1;
	if(L<=mid) clea(time, L, R, l, mid, root<<1);
	if(mid<R) clea(time, L, R, mid+1, r, root<<1|1);
	pushup(root);
}
int main() {
	freopen("in.txt","r",stdin);
	int n;
	memset(t,0,sizeof(t));
	scanf("%d",&n);
	build(1,n,1);
	int tm;
	scanf("%d",&tm);
	long long ans = 0;
	for(int i = 1; i <= tm; i++) {
		int time, l, r;
		scanf("%d%d%d",&time, &l, &r);
		recover(time, l, r, 1, n, 1);
		ans = (ans+query(l,r,1,n,1))%mod;
		clea(time,l,r,1,n,1);
	}
	printf("%lld\n", ans);
	return 0;
}