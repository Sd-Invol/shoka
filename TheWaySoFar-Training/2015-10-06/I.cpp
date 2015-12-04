#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
typedef long long LL;
using namespace std;
const int N = 2e5 + 5;

int a[N];
int f[N], g[N], h[N];

int main() {
    freopen("improvements.in", "r", stdin);
    freopen("improvements.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        a[x] = i;
    }
    memset(g, 63, sizeof(g));
    g[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int t = lower_bound(g, g + n + 1, a[i]) - g;
        f[i] = t;
        g[t] = a[i];
    }
    memset(g, 63, sizeof(g));
    g[0] = 0;
    for (int i = n; i > 0; --i) {
        int t = lower_bound(g, g + n + 1, a[i]) - g;
        h[i] = t;
        g[t] = a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, f[i] + h[i] - 1);
    printf("%d\n", ans);
    return 0;
}
