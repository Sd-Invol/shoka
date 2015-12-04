#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

const int N = 1e5 + 5;
typedef long long LL;
int a[N], b[N];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        LL ans = 0;
        for (LL p = 10; p <= 1000000000; p = p * 10) {
            for (int i = 1; i <= n; ++i)
                b[i] = a[i] % p;
            sort(b + 1, b + 1 + n);
            for (int i = n, j = 1; i >= 1; --i) {
                while (j < i && b[i] + b[j] < p) ++j;
                if (j >= i) break;
                ans += i - j;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}