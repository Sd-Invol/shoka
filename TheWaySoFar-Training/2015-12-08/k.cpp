#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 50005;

typedef long long LL;

const int P = 1e9 + 7;

int f[N][205], g[N][205];
int inv[N], I[N];

void init() {
    inv[0] = inv[1] = I[0] = I[1] = 1;
    for (int i = 2; i < N; ++i) {
        inv[i] = (LL)(P - P / i) * inv[P % i] % P;
        I[i] = i;
    }
    for (int i = 2; i < N; ++i) {
        I[i] = (LL)I[i] * I[i - 1] % P;
        inv[i] = (LL)inv[i] * inv[i - 1] % P;
    }
}

int C(int n, int m) {
    if (n < m) return 0;
    return (LL)I[n] * inv[m] % P * inv[n - m] % P;
}

int main() {
    init();
    f[0][0] = 1;
    for (int i = 0; i < N; ++i)
        g[i][0] = f[0][0] * inv[0];
    for (int i = 1; i < N; ++i)
        for (int j = 1; j <= 200; ++j) {
            f[i][j] = (LL)g[i - 1][j - 1] * I[i - 1] % P;
            g[i][j] = (g[i - 1][j] + (LL)f[i][j] * inv[i]) % P; 
        }
    int m;
    scanf("%d", &m);
    while (m --) {
        int n, a, b;
        scanf("%d%d%d", &n, &a, &b);
        /*int ans = 0;
        for (int i = 1; i <= n; ++i)
            ans = (ans + (LL)f[i - 1][a - 1] * f[n - i][b - 1] % P * C(n - 1, i - 1)) % P;
            printf("%d\n", ans);*/
        int res = (LL)C(a + b - 2, a - 1) * f[n - 1][a + b - 2] % P;
        printf("%d\n", res);
    }
    
    return 0;
}
