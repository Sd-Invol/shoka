#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 5e6 + 5;
typedef long long LL;

int main() {
    int n, m, K;
    while (scanf("%d%d%d", &n, &m, &K) == 3) {
        K /= 2;
        LL ans = 0;
        for (int i = 1; i <= n && i < K; ++i) {
            LL res = n - i + 1;
            int r1 = min(K - i, m), l1 = 1;
            l1 = m - l1 + 1;
            r1 = m - r1 + 1;
            //printf("%d %d %d\n", i, l1, r1);
                LL res1 = (LL)l1 * (l1 + 1) / 2 -
                (LL)r1 * (r1 - 1) / 2;
            ans += res * res1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}