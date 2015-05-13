#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

bool f[1 << 15][101], g[1 << 15][101];
int sum[1 << 15], a[1 << 15];

int main() {
    int n, X, Y;
    while (scanf("%d", &n), n) {
        scanf("%d%d", &X, &Y);
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[1 << i]);
        sum[0] = 0;
        for (int mask = 1; mask < 1 << n; ++mask) {
            int lowbit = mask & -mask;
            sum[mask] = sum[mask ^ lowbit] + a[lowbit];
        }
        static int ca = 0;
        printf("Case %d: ", ++ca);
        if (sum[(1 << n) - 1] != X * Y) {
            puts("No");
            continue;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= X; ++j) {
                if (sum[1 << i] % j != 0) continue;
                if (sum[1 << i] / j > Y) continue;
                f[1 << i][j] = 1;
            }
            for (int j = 1; j <= Y; ++j) {
                if (sum[1 << i] % j != 0) continue;
                if (sum[1 << i] / j > X) continue;
                g[1 << i][j] = 1;
            }
        }
        for (int mask = 1; mask < 1 << n; ++mask) {
            for (int i = 1; i <= X; ++i)
                if (sum[mask] % i == 0 && !f[mask][i]) {
                    if (sum[mask] / i > Y) continue;
                    for (int mask1 = mask - 1; mask1; mask1 = (mask1 - 1) & mask) {
                        f[mask][i] |= f[mask1][i] & f[mask ^ mask1][i];
                    }
                    g[mask][sum[mask] / i] |= f[mask][i];
                }
            for (int i = 1; i <= Y; ++i)
                if (sum[mask] % i == 0 && !g[mask][i]) {
                    if (sum[mask] / i > X) continue;
                    for (int mask1 = mask - 1; mask1; mask1 = (mask1 - 1) & mask) {
                        g[mask][i] |= g[mask1][i] & g[mask ^ mask1][i];
                    }
                    f[mask][sum[mask] / i] |= g[mask][i];
                }
        }
        if (f[(1 << n) - 1][X]) puts("Yes");
        else puts("No");
    }
    return 0;
}
