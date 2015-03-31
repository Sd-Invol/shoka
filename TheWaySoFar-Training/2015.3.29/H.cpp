#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int f[10005][2];

int main() {
    int n, S, F;
    scanf("%d%d%d", &n, &S, &F);
    if (S == F) {
        puts("-1");
        return 0;
    }
    memset(f, 63, sizeof(f));
    f[1][1] = 0;
    for (int i = 1; i < 10000; ++i) {
        f[i + 1][1] = min(f[i + 1][1], f[i][0] + 1);
        f[i + 1][1] = min(f[i + 1][1], f[i][1] + 1);
        f[i + 2][0] = min(f[i + 2][0], f[i][1]);
    }
    if (S > F) {
        S = n - S + 1;
        F = n - F + 1;
    }
    int ans = 0;
    if (S != 1) {
        ans = 1;
    }
    int res = ans;
    int len = F - S - 1;
    if (S == 1) ++len;
    ans += f[len][1];
    ans ++;
    if (F == n) ans = min(ans, res + f[len + 1][1]);
    if (ans > 1000000) ans = -1;
    printf("%d\n", ans);
    return 0;
}
