#include <bits/stdc++.h>
using namespace std;

int f[1 << 20][20], g[1 << 20][20];
int graph[20][20];

int main() {
    int n, m, ca = 0;
    while (scanf("%d%d", &n, &m) == 2) {
        int r = (n - 2) / 2;
        for (int i = 0; i < 1 << n; ++i)
            for (int j = 0; j < n; ++j)
                f[i][j] = g[i][j] = 1 << 28;
        memset(graph, 63, sizeof(graph));
        for (int i = 1; i <= m; ++i) {
            int x, y, t;
            scanf("%d%d%d", &x, &y, &t);
            graph[x][y] = graph[y][x] = min(graph[x][y], t);
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
        f[1][0] = g[1 << (n - 1)][n - 1] = 0;
        for (int mask = 0; mask < 1 << n; ++mask)
            if (__builtin_popcount(mask) <= r + 2) {
                for (int i = 0; i < n; ++i)
                    if (mask >> i & 1) {
                        for (int j = 0; j < n; ++j)
                            if (!(mask >> j & 1)) {
                                int mask1 = mask | (1 << j);
                                f[mask1][j] = min(f[mask1][j], f[mask][i] + graph[i][j]);
                                g[mask1][j] = min(g[mask1][j], g[mask][i] + graph[i][j]);
                                //printf("%d\n", graph[i][j]);
                            }
                    }
            }
        int ans = 1 << 28, S = (1 << n) - 1;
        for (int mask = 0; mask < 1 << n; ++mask)
            if (__builtin_popcount(mask) == r && !(mask & 1) && !(mask >> (n - 1) & 1)) {
                int ret0 = 1 << 28, ret1 = 1 << 28;
                int opt = mask ^ 1, opt1 = S ^ opt;
                for (int i = 0; i < n; ++i)
                    if (opt >> i & 1) {
                        for (int j = 0; j < n; ++j)
                            if (opt1 >> j & 1) {
                                ret0 = min(ret0, f[opt][i] + graph[i][j] + g[opt1][j]);
                            }
                    }
                opt = mask ^ (1 << (n - 1)), opt1 = S ^ opt;
                for (int i = 0; i < n; ++i)
                    if (opt >> i & 1) {
                        for (int j = 0; j < n; ++j)
                            if (opt1 >> j & 1) {
                                ret1 = min(ret1, g[opt][i] + graph[i][j] + f[opt1][j]);
                            }
                    }
                //printf("%d %d\n", ret0, ret1);
                ans = min(ans, ret0 + ret1);
            }
        printf("Case %d: %d\n", ++ca, ans);
    }
    return 0;
}
