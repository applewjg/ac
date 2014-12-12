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

const int maxn = 1005;
const int maxm = 10;
 
int f[maxn][1 << maxm], N, M, Q;
int W[maxn];
bool ok[1 << maxm];
void init() {
    for (int i = 0; i < (1 << M); i++) {
        int cnt = 0, val = i;
        while (val) {
            cnt += (val & 1); val >>= 1;
        }
        ok[i] = (cnt <= Q);
    }
}

int main() {
    freopen("in.txt","r",stdin);
    ios::sync_with_stdio(false);
    int ans = 0;
    scanf("%d%d%d", &N, &M, &Q);
    init();
    memset(f, -1, sizeof(f));
    memset(f[0], 0, sizeof(f[0]));
    for (int i = 1; i <= N; i++) scanf("%d", &W[i]);
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < (1 << M); j++) if(f[i - 1][j] != -1) {
            int s0 = ((j << 1) & ((1 << M) - 1)), s1 = ((j << 1 | 1) & ((1 << M) - 1));
            f[i][s0] = max(f[i - 1][j], f[i][s0]);
            if (ok[s1]) {
                f[i][s1] = max(f[i][s1], f[i - 1][j] + W[i]);
            }
        }
    }
    for (int i = 0; i < (1 << M); i++) {
        ans = max(ans, f[N][i]);
    }
    printf("%d\n", ans);
    return 0;
}
