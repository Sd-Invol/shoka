#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 55;

int xx[55], yy[55], zz[55], tx[55], ty[55], tz[55];
int sum[55];

int solve(int x[], int n, int a[]) {
    for (int i = 0; i < n; ++i) a[i] = x[i];
    sort(a, a + n);
    int m = unique(a, a + n) - a;
    for (int i = 0; i < n; ++i)
        x[i] = lower_bound(a, a + m, x[i]) - a;
    return m;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int r = 0;
    for (int i = 1; i <= n; ++i) {
        int x, y, K;
        scanf("%d%d%d", &x, &y, &K);
        while (K --) {
            int z;
            scanf("%d", &z);
            xx[r] = x, yy[r] = y, zz[r++] = z;
        }
    }
    int xn = solve(xx, r, tx);
    int yn = solve(yy, r, ty);
    int zn = solve(zz, r, tz);
    LL ans = 1LL << 60;
    for (int xl = 0; xl < xn; ++xl)
        for (int xr = xl; xr < xn; ++xr)
            for (int yl = 0; yl < yn; ++yl)
                for (int yr = yl; yr < yn; ++yr) {
                    for (int i = 0; i <= zn; ++i)
                        sum[i] = 0;
                    for (int i = 0; i < r; ++i)
                        if (xx[i] >= xl && xx[i] <= xr && yy[i] >= yl && yy[i] <= yr)
                            sum[zz[i] + 1] ++;
                    for (int i = 1; i <= zn; ++i)
                        sum[i] += sum[i - 1];
                    for (int i = 1, j = 0; i <= zn; ++i) {
                        while (sum[i] - sum[j + 1] >= m) ++j;
                        if (sum[i] - sum[j] >= m) {
                            ans = min(ans, (LL)(tx[xr] - tx[xl]) * (ty[yr] - ty[yl]) * (tz[i - 1] - tz[j]));
                        }
                    }
                }
    if (ans == 1LL << 60) ans = -1;
    printf("%lld\n", ans);
    return 0;
}
