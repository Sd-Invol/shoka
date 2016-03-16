#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int P = 998244353;
typedef long long LL;

int power[10000];

int main() {
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w", stdout);
    power[0] = 1;
    for (int i = 1; i <= 1000; ++i)
        power[i] = (LL)power[i - 1] * 2 % P;
    int n;
    while (scanf("%d", &n), n) {
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int t = n / i * i;
            if (t <= n) t += i;
            t %= n;
            t %= i;
            //printf("%d %d\n");
            ans = (ans + power[i - t]) % P;
        }
        printf("%d\n", ans);
    }
}
