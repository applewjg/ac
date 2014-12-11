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
int f[N][N] ={0};
int n,m,L;
int l, r, t, b;
int bad = 0;
int solve() {
	int ans = 0;
	//将臭水沟的位置放到右下角。
	if (l < m - r) {
		int temp = l;
		l = m - r;
		r = m - temp;
	}
	if (t < n - b) {
		int temp = t;
		t = n - b;
		b = n - temp;
	}
	for (int i = t + 1; i <= b; ++i) {
		for (int j = l + 1; j <= r; ++j) {
			f[i][j] = 1;
			++bad;
		}
	}
	if (L>=n*m) return n*m-bad;

	/*for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cout << f[i][j];
		}
		cout << endl;
	}*/
	int w,h;
	for (w = 1; w <= (L-2)/2 && w <= m; ++w) {
		for (h = 1; h <= (L - w*2) / 2 && h <= n; ++h) {
			if ((w<=r && h<=b) || (w<=l)|| (h<=t) || (w>=r&&h>=b)) {
				//这个case是画出来的矩形相交不横跨，或者包含或者完全不相交
				int tmp = 0;
				for (int i = 1; i <= h; ++i) {
					for (int j = 1; j <= w; ++j){
						if (f[i][j] == 1) ++tmp;
					}
				}
				ans = max(ans, w*h - tmp);
			} else if (w > l && w < r && h > t) {
				//横跨相交
 				if((w+h)*2+(w-l)*2 <= L) {
 					int tmp = 0;
					for (int i = 1; i <= h; ++i) {
						for (int j = 1; j <= w; ++j){
							if (f[i][j] == 1) ++tmp;
						}
					}
					ans = max(ans, w*h - tmp);
 				}
			} else if (w > r && h > t && h < b) {
				//横跨相交
 				if((w+h)*2+(h-t)*2 <= L) {
 					int tmp = 0;
					for (int i = 1; i <= h; ++i) {
						for (int j = 1; j <= w; ++j){
							if (f[i][j] == 1) ++tmp;
						}
					}
					ans = max(ans, w*h - tmp);
 				}
			}
		}
	}
	return ans;
}

int main(int argc, char const *argv[]) {
	/* code */
	freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);

	cin>>n>>m>>L;
	cin>>l>>r>>t>>b;
	int res = solve();
	cout << res <<endl;
	return 0;
}
/*
input:
4 4 14
1 3 1 3
*/
#include <cstdio>
#include <iostream>
using namespace std;
int i, j;
int work(int x0, int y0, int x1, int y1)
{
	int ret = i * j;
	int l = min(i, x1) - x0, k = min(j, y1) - y0;
	if (l < 0) l = 0;
	if (k < 0) k = 0;
	return ret - l * k;
}
int main1()
{
	freopen("in.txt","r",stdin);
	int ans = 0, x0, x1, y0, y1, L;
	cin >> n >> m >> L;
	cin >> x0 >> x1 >> y0 >> y1;
	for (i = 1; i < L / 2; i ++) {
		j = L / 2 - i;
		if (i > n || j > m) continue;
		ans =  max(ans, work(x0, y0, x1, y1));
		ans =  max(ans, work(x0, m - y1, x1, m - y0));
		ans =  max(ans, work(n - x1, m - y1, n - x0, m - y0));
		ans =  max(ans, work(n - x1, y0, n - x0, y1));
	}	
	cout << ans << endl;
	return 0;
}
