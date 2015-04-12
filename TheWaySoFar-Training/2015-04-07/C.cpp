#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;

const int P = 1e9 + 7;

int f[N];

int power(int a, int n) {
    int z = a, ans = 1;
    while (n) {
        if (n & 1) ans = (LL)ans * z % P;
        z = (LL)z * z % P;
        n >>= 1;
    }
    return ans;
}

int qsum(int a, int n) {
    if (a == 1) return n + 1;
    int res = (power(a, n + 1) - 1 + P) % P;
    res = (LL)res * power(a - 1, P - 2) % P;
    return res;
} // a^0 + ... + a^n

int col1[N], col2[N];

int main() {
    int b, k, h;
    scanf("%d%d%d", &b, &k, &h);
    f[1] = power(k, h);
    for (int i = 1; i <= h; ++i)
        scanf("%d", &col1[i]);
    for (int i = 1; i <= h; ++i)
        scanf("%d", &col2[i]);
    for (int i = 2; i <= b; ++i) 
        f[i] = (LL)f[i - 1] * qsum(k, h - 1) % P;
    int ans = 0;
    int z = qsum(k, h), sum = 0;
    for (int i = b - 1, j = 1; i > 0; --i, ++j) {
        sum = ((LL)sum * z + f[j]) % P;
        ans = ((LL)sum * f[i] + ans) % P;
    }
    ans = (LL)ans * power(power(k, h * 2), P - 2) % P;
    for (int i = h - 1; i >= 0; --i) {
        if (col1[i + 1] != col2[i + 1]) break;
        int res = (LL)power(qsum(k, i), b - 1) * power(k, h) % P;
        if (i != 0) {
            int ret = (LL)power(qsum(k, i - 1), b - 1) * power(k, h) % P;
            res = (res - ret + P) % P;
            //printf("!%d %d\n", res, ret);
        }
        res = (LL)res * power(power(k, i * 2 + (h - i)), P - 2) % P;
        //cout << res << endl;
        ans = (ans + (LL)res * b % P) % P;
    }
    printf("%d\n", ans);
    return 0;
}
