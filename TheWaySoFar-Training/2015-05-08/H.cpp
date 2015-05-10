#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 505;

int a[N];
int isset[N][N], isv[N][N];

void check(int L, int R, int &isset, int &isv) {
    static int bo[N];
    int m = 0, flag = 0;;
    for (int i = L; i <= R; ++i) {
        if (bo[a[i]]) flag = 1;
        ++bo[a[i]];
        m = max(a[i], m);
    }
    for (int i = L; i <= R; ++i)
        bo[a[i]] = 0;
    if (!flag) {
        if (m == (R - L + 1))
            isset = 1;
        isv = 1;
    }
}

int dp[N][N], f[N], g[N], ans[N];

void add(int x, int s, int f[]) {
    while (x > 0) {
        f[x] += s;
        x -= x & -x;
    }
}

int find(int x, int f[]) {
    int ans = 0;
    while (x < N) {
        ans += f[x];
        x += x & -x;
    }
    return ans;
}

int fm[N][N];

int main() {
    int n, q = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        fm[i][i] = a[i];
        for (int j = i + 1; j <= n; ++j)
            fm[i][j] = min(fm[i][j - 1], a[j]);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            check(i, j, isset[i][j], isv[i][j]);
    memset(dp, 63, sizeof(dp));
    for (int i = 1; i <= n; ++i)
        dp[i][i] = 0;
    for (int i = n - 1; i > 0; --i)
        for (int j = i + 1; j <= n; ++j) {
            if (!isv[i][j]) continue;
            memset(f, 0, sizeof(f));
            memset(g, 0, sizeof(g));
            for (int k = i; k <= j; ++k)
                add(a[k], 1, g);
            for (int k = i; k < j; ++k) {
                add(a[k], 1, f);
                add(a[k], -1, g);
                int S = find(fm[i][k], g) + find(fm[k + 1][j], f);
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + S);
                //if (i == 4 && j == 7)
                //    printf("%d %d %d %d\n", k, S, dp[i][k], dp[k + 1][j]);
            }
        }
    memset(ans, 63, sizeof(ans));
    ans[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j)
            if (isset[i + 1][j]) {
                ans[j] = min(ans[j], ans[i] + dp[i + 1][j]);
            }
    }
    if (ans[n] > (int)1e9) puts("impossible");
    else printf("%d\n", ans[n]);
    return 0;
}
