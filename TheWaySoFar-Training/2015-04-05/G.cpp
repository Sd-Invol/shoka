#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;

int C(LL n, LL m) {
    static int inv[100000];
    int ans = 1;
    if (m > 2000) m = n - m;
    for (int i = 1; i <= m; ++i) {
        if (i == 1) inv[i] = 1;
        else inv[i] = ((LL)P - P / i) * inv[P % i] % P;
        ans = (LL)ans * ((n - i + 1) % P) % P * inv[i] % P; 
    }
    //printf("%lld %lld\n", n, m);
    return ans;
}

int gett(LL n, LL m) {
    return C(n + m - 1, m - 1);
}

int main() {
    LL n, d, x;
    while (scanf("%lld%lld%lld", &n, &d, &x), n || d || x) {
        int ans = 0;
        for (int i = 0; i * x <= n && i <= d; ++i) {
            int res = (LL)gett(n - i * x, d) * C(d, i) % P;
            if (i & 1) ans = (ans + P - res) % P;
            else ans = (ans + res) % P;
        }
        printf("%d\n", ans);
    }
    return 0;
}
