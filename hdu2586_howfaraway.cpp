//============================================================================
// Name        : hdu2586.cpp
// Author      : 
// Description : 最近公共祖先
//============================================================================

#include <iostream>
#include <string.h>
#include <stdio.h>
#define NN 40002 // number of house
#define MM 202   // number of query
using namespace std;

typedef struct node{
    int v;
    int d;
    struct node *nxt;
}NODE;

NODE *Link1[NN];
NODE edg1[NN * 2]; // 树中的边

NODE *Link2[NN];
NODE edg2[NN * 2]; // 询问的点对

int idx1, idx2, N, M;
int res[MM][3]; // 记录结果，res[i][0]: u   res[i][1]: v  res[i][2]: lca(u, v)
int fat[NN];
int vis[NN];
int dis[NN];

void Add(int u, int v, int d, NODE edg[], NODE *Link[], int &idx){
    edg[idx].v = v;
    edg[idx].d = d;
    edg[idx].nxt = Link[u];
    Link[u] = edg + idx++;

    edg[idx].v = u;
    edg[idx].d = d;
    edg[idx].nxt = Link[v];
    Link[v] = edg + idx++;
}

int find(int x){ // 并查集路径压缩
    if(x != fat[x]){
        return fat[x] = find(fat[x]);
    }
    return x;
}

void Tarjan(int u){
    vis[u] = 1;
    fat[u] = u;

    for (NODE *p = Link2[u]; p; p = p->nxt){
        if(vis[p->v]){
            res[p->d][2] = find(p->v); // 存的是最近公共祖先结点
        }
    }

    for (NODE *p = Link1[u]; p; p = p->nxt){
        if(!vis[p->v]){
            dis[p->v] = dis[u] + p->d;
            Tarjan(p->v);
            fat[p->v] = u;
        }
    }
}
int main() {
    int T, i, u, v, d;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &N, &M);

        idx1 = 0;
        memset(Link1, 0, sizeof(Link1));
        for (i = 1; i < N; i++){
            scanf("%d%d%d", &u, &v, &d);
            Add(u, v, d, edg1, Link1, idx1);
        }

        idx2 = 0;
        memset(Link2, 0, sizeof(Link2));
        for (i = 1; i <= M; i++){
            scanf("%d%d", &u, &v);
            Add(u, v, i, edg2, Link2, idx2);
            res[i][0] = u;
            res[i][1] = v;
        }

        memset(vis, 0, sizeof(vis));
        dis[1] = 0;
        Tarjan(1);

        for (i = 1; i <= M; i++){
            printf("%d\n", dis[res[i][0]] + dis[res[i][1]] - 2 * dis[res[i][2]]);
        }
    }
    return 0;
}