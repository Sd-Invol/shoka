#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 5;
typedef long long LL;
const int P = 1e9 + 7;

int inv[N], I[N];

void init() {
    inv[0] = inv[1] = I[0] = I[1] = 1;
    for (int i = 2; i < N; ++i) {
        inv[i] = (LL)(P - P / i) * inv[P % i] % P;
        I[i] = i;
    }
    for (int i = 2; i < N; ++i) {
        inv[i] = (LL)inv[i] * inv[i - 1] % P;
        I[i] = (LL)I[i] * I[i - 1] % P;
    }
}

int C(int n, int m) {
    if (n < m) return 0;
    return (LL)I[n] * inv[m] % P * inv[n - m] % P;
}

int main() {
    init();
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int ans = 0, res = (LL)I[c + d] * inv[c] % P * inv[d] % P;
    a -= c;
    b -= d;
    for (int i = 0; i <= a; ++i)
        for (int j = 0; j <= b; ++j) {
            int tmp = (LL)I[i + j] * inv[i] % P * inv[j] % P;
            if (d != 0) { 
                tmp = (LL)tmp * C((a - i) + d - 1, d - 1) % P;
            }
            else if (a - i != 0) tmp = 0;
            if (c != 0) {
                tmp = (LL)tmp * C((b - j) + c - 1, c - 1) % P;
            }
            else if (b - j != 0) tmp = 0; 
            ans = (ans + (LL)tmp * res) % P;
          //  printf("%d %d %d\n", i, j, tmp);
        }
    cout << ans << endl;
    return 0;
}
