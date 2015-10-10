#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

typedef long long LL;

LL f[35][35][1805];
int a[35][35];

LL sqr(LL x) {
    return x * x;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                scanf("%d", &a[i][j]);
        memset(f, 63, sizeof(f));
        f[1][1][a[1][1]] = sqr(a[1][1]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                for (int k = 0; k <= 1770; ++k) {
                    f[i + 1][j][k + a[i + 1][j]] = min(f[i + 1][j][k + a[i + 1][j]], f[i][j][k] + sqr(a[i + 1][j]));
                    f[i][j + 1][k + a[i][j + 1]] = min(f[i][j + 1][k + a[i][j + 1]], f[i][j][k] + sqr(a[i][j + 1]));
                }
        LL ans = 1LL << 60;
        int len = n - 1 + m;
        for (int k = 0; k <= 1800; ++k) {
            if (f[n][m][k] > (1LL << 40)) continue;
            ans = min(ans, f[n][m][k] * len - sqr(k));
            //cout << sqr(k) << endl;
            //cout << f[n][m][k]   << endl;
        }
        static int ca = 0;
        printf("Case #%d: %lld\n", ++ca, ans);
    }
    return 0;
}