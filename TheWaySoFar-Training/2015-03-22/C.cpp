#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL f[1 << 16], g[1 << 16];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(f, 63, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int C;
        scanf("%d", &C);
        for (int mask = 0; mask < 1 << m; ++mask)
            g[mask] = f[mask];
        for (int j = 0; j < m; ++j) {
            int cost;
            scanf("%d", &cost);
            for (int mask = 1; mask < 1 << m; ++mask)
                if (mask >> j & 1)
                    g[mask] = min(g[mask], g[mask ^ (1 << j)] + cost);
        }
        for (int mask = 0; mask < 1 << m; ++mask)
            f[mask] = min(f[mask], g[mask] + C);
    }
    printf("%lld\n", f[(1 << m) - 1]);
    return 0;
}
