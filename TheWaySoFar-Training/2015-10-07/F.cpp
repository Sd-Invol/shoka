#include <iostream>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int ans = 0;

int TT[30000], r;
int LOG[1 << 20];
int n, m;

void dfs(int x, int mark, int mask) {
    if (x >= n) {
        TT[r++] = mask;
        return ;
    }
    dfs(x + 1, mark, mask);
    if (mark != (x & 1))
        dfs(x + 1, x & 1, mask | (1 << x));
}

int grid[500][20];
const int LIMIT = 1e9;

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < 20; ++i)
        LOG[1 << i] = i;
    for (int i = 2; i < 1 << 20; ++i)
        if (LOG[i] == 0) LOG[i] = LOG[i - 1];
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                scanf("%d", &grid[j][i]);
        r = 0;
        dfs(0, 100, 0);
        int ans = -LIMIT;
        for (int i = 0; i < r; ++i) {
            int f[2];
            int mask = TT[i];
            if (mask == 0) continue;
            f[0] = -LIMIT; f[1] = -LIMIT;
            for (int j = 0; j < m; ++j) {
                int x = mask, val = 0;
                while (x > 0) {
                    int t = x & -x;
                    val += grid[j][LOG[t]];
                    x -= t;
                }
                int g[2];
                g[0] = f[0];  g[1] = f[1];
                int q = j & 1;
                g[q] = max(max(0, f[q ^ 1]) + val, f[q]);
                f[0] = g[0];
                f[1] = g[1];
            }
            ans = max(max(f[0], f[1]), ans);
        }
        static int ca = 0;
        printf("Case #%d: %d\n", ++ca, ans);
    }
    return 0;
}