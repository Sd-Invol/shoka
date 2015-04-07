#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 105;
const int P = 1e9 + 7;

int n, m;
int f[N][2][2], C[N][N];

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

void work(int n) {
    static int g[N][N];
    memset(g, 0, sizeof(g));
    g[1][0] = n;
    for (int i = 1; i < n; ++i)
        for (int j = 0; j <= n; ++j)
            if (g[i][j]) {
                for (int k = 1; i + k <= n; ++k) {
                    int res = C[n - i - 1][k - 1];
                    updata(g[i + k][j + 1], (LL)res * f[k][1][0] % P * g[i][j] % P);
                    updata(g[i + k][j], (LL)res * f[k][0][0] % P * g[i][j] % P);
                }
            }
    for (int i = 0; i <= m; ++i) {
        
        updata(f[n][0][0], g[n][i]);
        if (i < m) updata(f[n][0][1], g[n][i]);
    }
}

int power(int a, int n) {
    int z = a, ans = 1;
    while (n) {
        if (n & 1) ans = (LL)ans * z % P;
        z = (LL)z * z % P; n >>= 1;
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
    }
    f[1][1][0] = f[1][1][1] = 1;
    for (int i = 2; i <= n; ++i)
        work(i);
    int ans = f[n][0][0];
    updata(ans, P - (LL)n * f[n - 1][0][0] % P);
    updata(ans, P - (LL)n * f[n - 1][1][0] % P);
    updata(ans, (LL)n * (f[n - 1][0][1] + f[n - 1][1][1]) % P);
    ans = (LL)ans * power(n, P - 2) % P;
    printf("%d\n", ans);
    
    return 0;
}
