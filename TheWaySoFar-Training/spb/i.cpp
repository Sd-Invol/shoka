#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;

typedef long long LL;

int h[N][2];
LL f[N][2];

int main() {
    int n;
    scanf("%d", &n);
    for (int j = 0; j < 2; ++j)
        for (int i = 1; i <= n; ++i)
            scanf("%d", &h[i][j]);
    memset(f, 63, sizeof(f));
    f[1][1] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 2; ++j)
            f[i][j] = min(f[i][j], f[i][j ^ 1] + abs(h[i][0] - h[i][1]));
        for (int j = 0; j < 2; ++j) {
            int K = h[i][j] - h[i + 1][j];
            if (j == 0) K = -K;
            if (K >= 0)
                f[i + 1][j] = min(f[i + 1][j], f[i][j]);
        }
    }
    LL ans = f[n][1];
    if (ans >= f[0][0]) ans = -1;
    for (int i = 1; i <= n; ++i)
        for (int j = max(1, i - 1); j <= min(n, i + 1); ++j)
            if (h[j][0] <= h[i][1]) {
                ans = -1;
                //printf("%d %d\n", i, j);
            }
    printf("%lld\n", ans);
    return 0;
}
