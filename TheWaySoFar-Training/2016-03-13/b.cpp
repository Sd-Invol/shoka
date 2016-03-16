#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

const int P = 1e9 + 9;

int c[10];
LL n;
int m;

struct Matrix {
    int n, m;

    int e[105][105];

    Matrix operator * (const Matrix &b) const {
        Matrix c;
        c.n = n;
        c.m = b.m;
        memset(c.e, 0, sizeof(c.e));
        for (int i = 0; i < c.n; ++i)
            for (int j = 0; j < c.m; ++j) {
                for (int k = 0; k < m; ++k) {
                    c.e[i][j] = (c.e[i][j] + (LL)e[i][k] * b.e[k][j]) % P;
                }
            }
        return c;
    }
}aa;

Matrix power(LL n) {
    Matrix ans, z;
    z = aa;
    ans = aa;
    --n;
    while (n > 0) {
        if (n & 1) ans = ans * z;
        n >>= 1;
        z = z * z;
    }
    return ans;
}

int dp[20];

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int num(int i, int j) {
    return i * 10 + j;
}

void add(int i, int j) {
    for (int k = 1; k <= m; ++k)
        for (int l = 1; l <= m; ++l) {
            if (i + 1 == k && i + 1 - k <= 9 &&
                j + 1 == l && j + 1 - l <= 9)
                updata(aa.e[num(i, j)][num(i + 1 - k, j + 1 - l)], (LL)c[k] * c[l] % P);
        }
    for (int k = 1; k <= m; ++k) {
        if (i + 1 == k && i + 1 - k <= 9 &&
            j + 1 <= 9)
            updata(aa.e[num(i, j)][num(i + 1 - k, j + 1)], (LL)c[k] % P);
        if (j + 1 == k && j + 1 - k <= 9 &&
            i + 1 <= 9)
            updata(aa.e[num(i, j)][num(i + 1, j + 1 - k)], (LL)c[k] % P);

    }
    if (i == j && i == 0) {
        updata(aa.e[num(i, j)][num(i, j)], c[2]);
    }
    return ;
}

int main() {
    scanf("%lld%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d", &c[i]);
    memset(aa.e, 0, sizeof(aa.e));
    aa.n = 10 * 10, aa.m = 10 * 10;
    for (int i = 0; i <= 9; ++i)
        for (int j = 0; j <= 9; ++j) {
            add(i, j);
            if (i + 1 <= 9 && j + 1 <= 9)
                updata(aa.e[num(i, j)][num(i + 1, j + 1)], 1);
        }
    Matrix d;
    d.n = 1, d.m = 100;
    memset(d.e, 0, sizeof(d.e));
    //   cout << aa.e[0][0] << endl;
    d.e[0][0] = 1;
    // d = d * power(1);
    //for (int i = 0; i < 2; ++i)
    //    for (int j = 0; j < 2; ++j)
    //       printf("(%d, %d) = %d\n", i, j, d.e[0][num(i, j)]);
    d = d * power(n);

    int ans = d.e[0][0];
    printf("%d\n", ans);
    return 0;
}
