#include <bits/stdc++.h>
using namespace std;

const int N = 305;
int f[N][N][N], C[N * 2][N * 2];
const int P = 1e9 + 9;

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

typedef long long LL;

int main() {
    int n, K;
    scanf("%d%d", &n, &K);
    f[0][0][0] = 1;
    for (int i = 0; i < N; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j)
            for (int k = 0; k <= K; ++k) {
                updata(f[i + 1][j + 1][max(k, j + 1)], f[i][j][k]);
                if (j > 0)
                    updata(f[i + 1][j - 1][k], f[i][j][k]);
            }
    int ans = 0;
    for (int i = 0; i <= n; ++i)
        if (f[i][0][K]) {
            LL res = f[i][0][K];
            res = res * C[(i + 1) + (n - i) - 1][(i + 1) - 1] % P;
            // i + 1, n - i
            updata(ans, res);
        }
    printf("%d\n", ans);
    return 0;
}
