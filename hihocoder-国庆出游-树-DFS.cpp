//#pragma comment(linker, "/STACK:102400000,102400000")  
#include <cstdio>
#include <cstdlib>
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
#include <list>
#include <bitset>
using namespace std;  
#define MP(x,y) make_pair((x),(y))  
#define PB(x) push_back(x)
#define ini(a) memset(a,0,sizeof(a))   
typedef long long ll;
const int mod=1000000007;

#define N 105

std::vector<int> G[N];
bitset<N> f[N];
bool cango[N][N];
int a[N];
int n, m;
int now;
bool ok;
int c;

void dfs(int u, int fa) {
	f[u][u] = 1;
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(v==fa) continue;
		dfs(v,u);
		f[u]|=f[v];
	}
}
void solve(int u, int fa) {
	if (c < m && a[c] == u) c++;
	if (c == m) {
		ok = 1;
		return;
	}
	while (c < m) {
		int nex = a[c];
		int cur = c;
		for (int i = 0; i<G[u].size();++i) {
			int v = G[u][i];
			if (v == fa) continue;
			if(f[v][nex] && cango[u][v]) {
				cango[u][v]=0;
				solve(v,u);
				break;
			}
		}
		if(c == cur) break;
	}
}
int main() {
	freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--) {
		cin >> n;
		ini(cango);
		for (int i = 1; i <= n; ++i) {
			f[i].reset();
			G[i].clear();
		}
		for (int i=1;i<=n-1;++i) {
			int u,v;
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
			cango[u][v] = cango[v][u] = 1;
		}
		cin >> m;
		for (int i = 0; i<m; ++i) {
			cin >> a[i];
		}
		dfs(1,-1);
		c = 0;
		ok = 0;
		solve(1,-1);
		if(ok) puts("YES");
		else puts("NO");
	}
	return 0;
}