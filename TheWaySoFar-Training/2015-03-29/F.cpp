#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1000005;
int bo[N], prime[N];
const int P = 1e9 + 9;

int power(int a, int n) {
    int ans = 1, z = a;
    while (n) {
        if (n & 1) ans = (LL)ans * z % P;
        z = (LL)z * z % P; n >>= 1;
    }
    return ans;
}

int ver[1000], alll[1000], num[N];
double f[17][1 << 16];
pair<int, int> pre[17][1 << 16];
int mul[1 << 16];
pair<int, int> pri[100];

int main() {
    int n;
    scanf("%d", &n);
    int m = 0;
    for (int i = 2; i < N; ++i)
        if (!bo[i]) {
            prime[m++] = i;
            for (int j = i * 2; j < N; j += i)
                bo[j] = 1;
        }
    int res = 0;
    int p = 0;
    mul[0] = 1;
    for (int i = 0; i < m; ++i)
        while (n % prime[i] == 0) {
            n /= prime[i];
            mul[1 << p] = prime[i];
            ver[p++] = prime[i];
        }
    for (int mask = 1; mask < 1 << p; ++mask) {
        int x = mask & -mask;
        mul[mask] = mul[mask ^ x] * mul[x];
    }
    int ans = 1, T = 0;
    for (int i = 0; i < 1 << p; ++i) {
        int flag = 1;
        for (int j = 1; j < p; ++j)
            if (ver[j] == ver[j - 1] && (i >> j & 1) && !(i >> (j - 1) & 1))
                flag = 0;
        if (flag) alll[T++] = i;
    }
    for (int i = 0; i <= p; ++i)
        for (int mask = 0; mask < 1 << p; ++mask) {
            f[i][mask] = 1e60;
        }
    f[0][0] = 0;
    for (int i = 0; i < p; ++i)
        for (int mask = 0; mask < T; ++mask)
            if (f[i][alll[mask]] < 1e30) {
                for (int mask1 = 0; mask1 < T; ++mask1) {
                    for (int j = 0; j < p; ++j) num[ver[j]] = 0;
                    int opt1 = alll[mask], opt2 = alll[mask1];
                    int S = 0;
                    for (int j = 0; j < p; ++j) {
                        if (opt1 >> j & 1) ++num[ver[j]], ++S;
                        if (opt2 >> j & 1) ++num[ver[j]], ++S;
                    }
                    int opt3 = 0;
                    for (int j = 0; j < p; ++j) 
                        if (num[ver[j]]) {
                            opt3 |= 1 << j;
                            --S;
                            --num[ver[j]];
                        }
                    if (S) continue;
                    double s = f[i][opt1] + (mul[opt2] - 1) * log(prime[i + 1]);
                    if (s < f[i + 1][opt3]) {
                        f[i + 1][opt3] = s;
                        pre[i + 1][opt3] = make_pair(opt1, opt2);
                    }
                }
            }
    int x = p, y = (1 << p) - 1;
    while (x > 0) {
        ans = (LL)ans * power(prime[x], mul[pre[x][y].second] - 1) % P;
        y = pre[x][y].first;
        --x;
    }
    printf("%d\n", ans);
    return 0;
}
