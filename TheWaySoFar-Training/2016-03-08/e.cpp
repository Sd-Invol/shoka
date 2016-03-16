#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

typedef long long LL;

LL dp[2][1 << 14][15];
int n, p[30], b[30], m;

void updata(LL &x, LL y) {
    x += y;
    
}

LL solve(int i, int x, int mask, int &j) {
    LL fac = 1;
    if (x + 2 <= n && (mask >> (x / 2 + 1) & 1) == 0) {
        if (p[x + 1] == 0) {
            fac *= j;
            --j;
        }
        else {
            if (p[x + 1] * 2 > i) return 0;
        }
    }
    if (x - 2 > 0 && (mask >> (x / 2 - 1) & 1) == 0) {
        if (p[x - 1] == 0) {
            fac *= j;
            --j;
        }
        else {
            if (p[x - 1] * 2 > i) return 0;
        }
    }
    if (j < 0) return 0;
    return fac;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &p[i]);
        //p[i] = 0;
        if (p[i] != 0) {
            b[p[i]] = i;
        }
    }
    int m = n / 2 + 1;
    for (int i = 1; i <= n; ++i)
        if (p[i] != 0) {
            if (p[i] < m && (i % 2 == 1)) {
                puts("0");
                return 0;
            }
            if (p[i] >= m && (i % 2 == 0)) {
                puts("0");
                return 0;
            }
            if (i + 1 <= n && p[i + 1] != 0) {
                int mn = min(p[i], p[i + 1]);
                int mx = max(p[i], p[i + 1]);
                if (mx < mn * 2) {
                    puts("0");
                    return 0;
                }
            }
        }
    int S = n - m + 1;
    int cur = 0, nex = 1, tmp = 0;
    for (int i = 1; i <= m - 1; ++i)
        if (i * 2 <= m - 1 && b[i] == 0) ++tmp;
    dp[cur][0][tmp] = 1;
    for (int i = m; i <= n; ++i) {
        memset(dp[nex], 0, sizeof(dp[nex]));
        for (int mask = 0; mask < 1 << S; ++mask)
            for (int j = 0; j <= 14; ++j)
                if (dp[cur][mask][j]) {
                    int J = j;
                    //   puts("1");
                    if (i % 2 == 0 && (b[i / 2] == 0)) ++J;
                    for (int k = 1; k <= n; k += 2)
                        if ((b[i] == k) || (b[i] == 0 && p[k] == 0)) {
                            if (mask >> (k >> 1) & 1) continue;
                            int _j = J;
                            LL tmp = solve(i, k, mask, _j);
                            if (tmp != 0)
                                updata(dp[nex][mask | (1 << (k >> 1))][_j], dp[cur][mask][j] * tmp);
                        }
                    //puts("2");
                }
        swap(cur, nex);
    }
    LL ans = dp[cur][(1 << S) - 1][0];
    cout << ans << endl;
    return 0;
}
