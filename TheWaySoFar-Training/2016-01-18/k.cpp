#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

const int N = 1e5 + 5;
const int D = 20;

int first[N], tot;

struct Edge {
    int y, s, nex;
}edge[N << 1];

void addedge(int x, int y, int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}

int dep[N], parent[D][N];

void lca_init(int x, int fa) {
    dep[x] = dep[fa] + 1;
    parent[0][x] = fa;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y != fa) lca_init(y, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = D - 1; i >= 0; --i)
        if (dep[parent[i][x]] >= dep[y]) {
            x = parent[i][x];
        }
    if (x == y) return x;
    for (int i = D - 1; i >= 0; --i)
        if (parent[i][x] != parent[i][y]) {
            x = parent[i][x];
            y = parent[i][y];
        }
    return parent[0][x];
}

int sum[N];

void dfs_init(int x, int fa) {
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        dfs_init(y, x);
        sum[x] += sum[y];
        edge[k].s = edge[k ^ 1].s = sum[y];
    }
}

typedef long long LL;

LL f[N], ans1 = 0, ans2 = 0, g[N];

void dp1(int x, int fa) {
    f[x] = 0;
    LL mx = 0;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        dp1(y, x);
        f[x] += f[y];
        mx = max(mx, (LL)edge[k].s);
    }
    f[x] += mx;
}


void dp2(int x, int fa) {
    LL sum = 0;
    int mx1 = tot + 1, mx2 = tot + 1;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y != fa) {
            sum += f[y];
        }
        else sum += g[y];
        if (edge[k].s > edge[mx1].s) mx2 = mx1, mx1 = k;
        else if (edge[k].s > edge[mx2].s) mx2 = k;
    }
    //printf("!%d %lld %lld\n", x, sum, edge[0].s);
    ans2 = max(ans2, sum + edge[mx1].s);
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        g[x] = sum - f[y];
        if (mx1 == k) g[x] += edge[mx2].s;
        else g[x] += edge[mx1].s;
        dp2(y, x);
    }
}

int main() { 
    int n, q;
    scanf("%d%d", &n, &q);
    memset(first, -1, sizeof(first));
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y, 0);
        addedge(y, x, 0);
    }
    lca_init(1, 0);
    for (int i = 1; i < D; ++i)
        for (int j = 1; j <= n; ++j)
            parent[i][j] = parent[i - 1][parent[i - 1][j]];
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        int z = lca(x, y);
        sum[x]++;
        sum[y]++;
        sum[z] -= 2;
        ans1 += dep[x] - dep[z] + dep[y] - dep[z];
    }
    dfs_init(1, 0);
    dp1(1, 0);
    dp2(1, 0);
    cout << ans1 - ans2 << endl;
    return 0;
}
/*
4 3
1 2
2 3
2 4
1 3
1 4
3 4
*/
