#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

const int N = 50005;
typedef unsigned long long ULL;
int a[N], sum[N], b[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        ULL res0 = 0, res1 = 0, res2 = 0;
        for (int j = 0; j <= 30; ++j) {
            ULL ans0 = 0, ans1 = 0, ans2 = (ULL)n * (n + 1) / 2;
            for (int i = 1, p = 0; i <= n; ++i) {
                b[i] = (a[i] >> j & 1);
                sum[i] = sum[i - 1] ^ (a[i] >> j & 1);
                if (sum[i] == 0) {
                    ans0 += p;
                }
                else ans0 += i - p;
                if (sum[i] == 1) p++;
            }
            for (int i = 1; i <= n; ++i)
                if (b[i] == 1) {
                    int r = i;
                    while (r < n && b[r + 1] == 1) ++r;
                    int len = r - i + 1;
                    ans1 += (ULL)len * (len + 1) / 2;
                    i = r;
                }
            for (int i = 1; i <= n; ++i)
                if (b[i] == 0) {
                    int r = i;
                    while (r < n && b[r + 1] == 0) ++r;
                    int len = r - i + 1;
                    ans2 -= (ULL)len * (len + 1) / 2;
                    i = r;
                }
            res0 += ans0 * (1LL << j);
            res1 += ans1 * (1LL << j);
            res2 += ans2 * (1LL << j);
        }
        static int ca = 0;
        ULL sum = (ULL)n * (n + 1) / 2;
        printf("Case #%d: %.6f %.6f %.6f\n", ++ca, (double)res1 / sum, (double)res2 / sum, (double) res0 / sum);
    }
    return 0;
}