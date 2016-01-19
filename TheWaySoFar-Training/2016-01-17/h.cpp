#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int M = 5e4 + 5;

int f[2][M][2];
pair<int, int> a[10000];

void updata(int &x, int y) {
    x = max(x, y);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    sort(a + 1, a + 1 + n);
    memset(f, -1, sizeof(f));
    int cur = 0, nex = 1;
    f[cur][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        memset(f[nex], -1, sizeof(f[nex]));
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k < 2; ++k)
                if (f[cur][j][k] != -1) {
                    int K = k;
                    if (i == 1 || a[i].first != a[i - 1].first)
                        K = 0;
                    updata(f[nex][j][K], f[cur][j][k]);
                    int s = 0;
                    if (K == 0) s = 1;
                    if (j + a[i].second <= m)
                        updata(f[nex][j + a[i].second][1], f[cur][j][k] + s);
                }
        swap(cur, nex);
    }
    int ans = max(f[cur][m][0], f[cur][m][1]);
    if (ans == -1) puts("Impossible");
    else printf("%d\n", ans);
    return 0;
}
