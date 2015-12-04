#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
const int N = 1e5 + 5;
const int D = 20;
using namespace std;

int parent[D][N];
int first[N], tot;

struct Edge {
    int y, nex;
}edge[N << 1];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int w[D][N], dep[N];

void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        parent[0][y] = x;
        w[0][y] = 1 << (k & 1);
        dfs(y, x);
    }
}

int lca(int x, int y) {
    int a = 2, b = 1;
    if (dep[x] < dep[y]) {
        swap(x, y);
        swap(a, b);
    }
    for (int i = D - 1; i >= 0; --i)
        if (dep[parent[i][x]] >= dep[y]) {
            if (w[i][x] != a) return 0;
            x = parent[i][x];
        }
    if (x == y) return 1;
    for (int i = D - 1; i >= 0; --i)
        if (parent[i][x] != parent[i][y]) {
            if (w[i][x] != a) return 0;
            if (w[i][y] != b) return 0;
            x = parent[i][x];
            y = parent[i][y];
        }
    if (w[0][x] != a) return 0;
    if (w[0][y] != b) return 0;
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    memset(first, -1, sizeof(first));
    tot = 0;
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
    }
    dfs(1, 0);
    for (int i = 1; i < D; ++i)
        for (int j = 1; j <= n; ++j) {
            int p = parent[i - 1][j];
            parent[i][j] = parent[i - 1][p];
            w[i][j] = w[i - 1][j] | w[i - 1][p];
        }
    int m;
    scanf("%d", &m);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (lca(x, y)) puts("Yes");
        else puts("No");
    }
    return 0;
}