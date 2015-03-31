#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 605;

int ll[N], rr[N], R[N];
int b[N], pos[N][N];
int dp[N][N];

void work() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d%d%d", &ll[i], &rr[i], &R[i]);
    int m = 0;
    for (int i = 0; i < n; ++i) {
        b[m++] = ll[i];
        b[m++] = rr[i];
    }
    sort(b, b + m);
    m = unique(b, b + m) - b;
    for (int i = 0; i < n; ++i) {
        ll[i] = lower_bound(b, b + m, ll[i]) - b;
        rr[i] = lower_bound(b, b + m, rr[i]) - b;
        //printf("%d %d\n", ll[i], rr[i]);
    }
    for (int i = 0; i < m; ++i)
        for (int j = 0; j <= i; ++j)
            pos[i][j] = 0, dp[j][i] = 1 << 29;
    for (int i = m - 1; i >= 0; --i) {
        for (int j = 0; j < n; ++j)
            if (ll[j] == i)
                for (int k = i; k <= rr[j]; ++k)
                    pos[rr[j]][k] = max(pos[rr[j]][k], R[j]);
        for (int j = i + 1; j < m; ++j)
            for (int k = i; k <= j; ++k)
                pos[j][k] = max(pos[j][k], pos[j - 1][k]);
        for (int j = i; j < m; ++j)
            for (int k = i; k <= j; ++k) {
                int s = pos[j][k];
                if (k != i) s += dp[i][k - 1];
                if (k != j) s += dp[k + 1][j];
                //printf("%d %d %d %d\n", i, j, k, s);
                dp[i][j] = min(dp[i][j], s);
            }
    }
    // printf("%d\n", m);
    printf("%d\n", dp[0][m - 1]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) work();
    return 0;
}
